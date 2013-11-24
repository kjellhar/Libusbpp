#include <QSharedPointer>
#include <iostream>

#include "deviceimpl.h"
#include "device.h"

QLibUsb::DeviceImpl::DeviceImpl(libusb_device* pDevice)
{
    // Add a reference to pDevice and save it.
    m_pDevice.reset(libusb_ref_device(pDevice), DeviceDeleter());
}


QSharedPointer<libusb_device_descriptor> QLibUsb::DeviceImpl::getDeviceDescriptor()
{
    if (m_pDeviceDescriptor.isNull())
    {
        m_pDeviceDescriptor.reset(new libusb_device_descriptor);
        // Obtain the usb device descriptors
        int Result = libusb_get_device_descriptor(m_pDevice.data(), m_pDeviceDescriptor.data());
/*        if (Result != LIBUSB_SUCCESS)
        {
            throw std::exception("libusb_get_device_descriptor() failed.");
        }
*/
    }

    return m_pDeviceDescriptor;

}


bool QLibUsb::DeviceImpl::isOpen() const
{

    return (!m_pHandle.isNull());

}

void QLibUsb::DeviceImpl::Open()
{

    if (m_pDevice.isNull())
    {
//        throw std::exception("Open() failed - (There is no device!)");
    }

    if (m_pHandle.isNull())
    {

        // Open the device
        libusb_device_handle* pHandle;
        int Result = libusb_open(m_pDevice.data(), &pHandle);

/*        if (Result != LIBUSB_SUCCESS)
        {

            throw LibUSBException("libusb_open() failed.", Result);

        }
*/
        m_pHandle.reset(pHandle, DeviceHandleDeleter());

    }
}

QString QLibUsb::DeviceImpl::getStringDescriptor( uint8_t index )
{


    unsigned char descStr[512];
    memset(descStr, 0, sizeof(descStr));

    int Result = libusb_get_string_descriptor_ascii(m_pHandle.data(), index, descStr, sizeof(descStr));

/*    if (Result < LIBUSB_SUCCESS)
    {
        throw LibUSBException("libusb_get_string_descriptor_ascii() failed.", Result);
    }
*/
    //std::string strResult;
    //strResult.assign((const char*)descStr);

    return QString((const char*)descStr);
}

/*
uint16_t QLibUsb::DeviceImpl::getLangId()
{

    /// \note This descriptor is described here: http://www.beyondlogic.org/usbnutshell/usb5.shtml

    if((languageId == 0) && isOpen())
    {
        uint8_t data[255];
        memset(data, '\0', sizeof(data));
        int Result = libusb_get_string_descriptor(m_pHandle.get(), 0, 0, data, sizeof(data));
        if (Result < LIBUSB_SUCCESS)
        {
            throw LibUSBException("libusb_get_string_descriptor() failed.", Result);
        }

        // First element is the size of the descriptor, in bytes
        uint8_t descriptorSize = data[0];

        // Second element should be 0x03
        if (data[1] != 0x03)
        {
            throw std::runtime_error("USB language string descriptor (index 0) is invalid.");
        }

        // Grab the first/default language.
        languageId = data[2] | data[3]<<8;

    }

    return languageId;

}
*/

bool QLibUsb::DeviceImpl::getActiveConfiguration( uint8_t &ConfigValue )const
{
    // Obtain the currently active config
    libusb_config_descriptor * pConfig;

    int Result = libusb_get_active_config_descriptor(m_pDevice.data(), &pConfig);

/*    if (Result != LIBUSB_SUCCESS)
    {
        switch(Result)
        {
        case LIBUSB_ERROR_NOT_FOUND:

            // The device is in an unconfigured state.
            ConfigValue = 0;
            return false;
            break;

        default:
            throw LibUSBException("libusb_get_active_config_descriptor() failed. ", Result);
            return false;
            break;
        }
    }
*/
    // Obtain the index
    ConfigValue = pConfig->bConfigurationValue;

    return true;

}
/*
std::shared_ptr<LibUSB::Configuration> LibUSB::DeviceImpl::getConfiguration( uint8_t ConfigValue )
{
    // Check for an existing object.
    if((m_ConfigurationMap.find(ConfigValue) != m_ConfigurationMap.end()) && (m_ConfigurationMap[ConfigValue].expired()))
    {

        return m_ConfigurationMap[ConfigValue].lock();

    }

    // Create a new configuration object
    libusb_config_descriptor* pConfig = nullptr;

    int Result = libusb_get_config_descriptor_by_value(m_pDevice.get(), ConfigValue, &pConfig);

    if (Result != LIBUSB_SUCCESS)
    {
        std::stringstream exceptionText;
        exceptionText << "libusb_get_config_descriptor() failed";

        switch(Result)
        {
        case LIBUSB_ERROR_NOT_FOUND:

            exceptionText << "(index " << (int)ConfigValue << ")";
            break;

        default:
            break;
        }

        throw LibUSBException(exceptionText.str(), Result);

    }

    std::shared_ptr<ConfigurationImpl> pConfigImpl = std::make_shared<LibUSB::ConfigurationImpl>(pConfig, this->shared_from_this());

    std::shared_ptr<Configuration> pConfigurationObj = std::make_shared<LibUSB::Configuration>(pConfigImpl);

    // Save a weak_ptr to the configuration object to prevent duplication.
    m_ConfigurationMap.insert(std::make_pair(ConfigValue, pConfigurationObj));

    return pConfigurationObj;

}
*/

void QLibUsb::DeviceImpl::setActiveConfiguration( uint8_t ConfigValue )
{

    // Set the active configuration.
    int Result = libusb_set_configuration(m_pHandle.data(), ConfigValue);
/*
    if (Result != LIBUSB_SUCCESS)
    {
        std::stringstream exceptionText;
        exceptionText << "libusb_set_configuration() failed. (index " << (int)ConfigValue << ") ";

        switch(Result)
        {
        case LIBUSB_ERROR_NOT_FOUND:

            exceptionText << "The requested configuration does not exist.";
            break;

        case LIBUSB_ERROR_BUSY:

            exceptionText << "Interfaces are currently claimed.";
            break;

        case LIBUSB_ERROR_NO_DEVICE:

            exceptionText << "Device has been disconnected.";
            break;

        default:
            break;
        }

        throw LibUSBException(exceptionText.str(), Result);

    }
*/
}

QWeakPointer<QLibUsb::Device> QLibUsb::DeviceImpl::getDevice() const
{

    if (m_ParentDevice.isNull())
    {
//        throw std::logic_error("LibUSB::DeviceImpl::getDevice() - expired pointer to parent LibUSB::Device object.");
    }

    return m_ParentDevice;

}

void QLibUsb::DeviceImpl::setParentDevice( QWeakPointer<Device> pParentDevice )
{

    if (pParentDevice.isNull())
    {
//        throw std::logic_error("LibUSB::DeviceImpl::setParentDevice() - new parent device pointer is expired.");
    }

    m_ParentDevice = pParentDevice;
}

/*
std::shared_ptr<LibUSB::Endpoint> LibUSB::DeviceImpl::getControlEndpoint()
{

    if (m_pEndpointZero.get() == nullptr)
    {

        // Initialize Endpoint Zero Dummy Descriptor
        m_EndpointZeroDescriptor.bLength = 0x07;
        m_EndpointZeroDescriptor.bDescriptorType = libusb_descriptor_type::LIBUSB_DT_ENDPOINT;
        m_EndpointZeroDescriptor.bEndpointAddress = 0;
        m_EndpointZeroDescriptor.bmAttributes = 0;
        m_EndpointZeroDescriptor.wMaxPacketSize = getDeviceDescriptor()->bMaxPacketSize0;
        m_EndpointZeroDescriptor.bInterval = 0;

        // All your endpoints are belong to us.
        std::shared_ptr<LibUSB::EndpointImpl> pEPImpl = std::make_shared<LibUSB::EndpointImpl>(&m_EndpointZeroDescriptor, shared_from_this());
        m_pEndpointZero = std::make_shared<LibUSB::Endpoint>(pEPImpl);

    }

    return m_pEndpointZero;

}
*/
