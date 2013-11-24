#include <QSharedPointer>
#include <QString>

#include "device.h"
#include "libusb.h"

QLibUsb::Device::Device(libusb_device* pDevice)
{
    m_pDevice.reset(libusb_ref_device(pDevice), DeviceDeleter());
    getDeviceDescriptor();
}


uint16_t QLibUsb::Device::USBSpecification()
{

    return m_pDeviceDescriptor->bcdUSB;

}

uint8_t QLibUsb::Device::DeviceClass()
{
    return m_pDeviceDescriptor->bDeviceClass;
}


uint8_t QLibUsb::Device::DeviceSubclass()
{
    return m_pDeviceDescriptor->bDeviceSubClass;
}

uint8_t QLibUsb::Device::DeviceProtocol()
{
    return m_pDeviceDescriptor->bDeviceProtocol;
}

uint16_t QLibUsb::Device::vendorID()
{
    return m_pDeviceDescriptor->idVendor;
}

uint16_t QLibUsb::Device::productID()
{
    return m_pDeviceDescriptor->idProduct;
}

uint8_t QLibUsb::Device::NumConfigurations()
{
    return m_pDeviceDescriptor->bNumConfigurations;
}

QString QLibUsb::Device::ProductString()
{

    // Device must be open
    if (!isOpen())
    {

//        throw std::runtime_error("ProductString() - device must be open!");
        return QString("Device must be open");

    }

    // Validate the descriptor index
    if(m_pDeviceDescriptor->iProduct == 0)
    {
        // throw std::runtime_error("Serial Number is not supported on this device.");
        return QString("Not supported.");
    }


    unsigned char descStr[512];
    memset(descStr, 0, sizeof(descStr));

    int Result = libusb_get_string_descriptor_ascii(m_pHandle.data(), m_pDeviceDescriptor->iProduct, descStr, sizeof(descStr));

/*    if (Result < LIBUSB_SUCCESS)
    {
        throw LibUSBException("libusb_get_string_descriptor_ascii() failed.", Result);
    }
*/
    return QString((const char*)descStr);
}

/*
QString QLibUsb::Device::ManufacturerString()
{

    // Device must be open
    if (!isOpen())
    {

//        throw std::runtime_error("ProductString() - device must be open!");

    }

    // Validate the descriptor index
    if(m_pDeviceDescriptor->iManufacturer == 0)
    {
        // throw std::runtime_error("Serial Number is not supported on this device.");
        return L"Not supported.";
    }

    // Return a manufacturer string.
    QString resultStr = m_pDeviceImpl_->getStringDescriptorW(m_pDeviceDescriptor->iManufacturer);

    return resultStr;

}
*/

QString QLibUsb::Device::SerialString()
{

    // Device must be open
    if (!isOpen())
    {

//        throw std::runtime_error("ProductString() - device must be open!");

    }

    // Validate the descriptor index
    if(m_pDeviceDescriptor->iSerialNumber == 0)
    {
        // throw std::runtime_error("Serial Number is not supported on this device.");
        return QString("Not supported.");
    }

    unsigned char descStr[512];
    memset(descStr, 0, sizeof(descStr));

    int Result = libusb_get_string_descriptor_ascii(m_pHandle.data(), m_pDeviceDescriptor->iSerialNumber, descStr, sizeof(descStr));

/*    if (Result < LIBUSB_SUCCESS)
    {
        throw LibUSBException("libusb_get_string_descriptor_ascii() failed.", Result);
    }
*/
    return QString((const char*)descStr);

}

void QLibUsb::Device::Open()
{
    if (m_pDevice.isNull())
    {
//        throw std::exception("Open() failed - (There is no device!)");
        return;
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

bool QLibUsb::Device::isOpen()
{
    return (!m_pHandle.isNull());

}

/*
QSharedPointer<QLibUsb::Configuration> QLibUsb::Device::getConfiguration( uint8_t ConfigValue )
{

    // Check the active configuration object
    if ((m_pActiveConfiguration.get() != nullptr) && (m_pActiveConfiguration->Value() == ConfigValue))
    {
        return m_pActiveConfiguration;
    }

    // Create a configuration object
    return m_pDeviceImpl_->getConfiguration(ConfigValue);
}
*/
/*
std::shared_ptr<LibUSB::Configuration> LibUSB::Device::getActiveConfiguration()
{

    // Get the index of the active configuration
    uint8_t index = 0;

    if (m_pDeviceImpl_->getActiveConfiguration(index))
    {
        // Check the active configuration object
        if ((m_pActiveConfiguration.get() == nullptr) || (m_pActiveConfiguration->Value() != index))
        {
            // Create a new object
            m_pActiveConfiguration = m_pDeviceImpl_->getConfiguration(index);
        }
    }
    else
    {
        // The device is unconfigured - return a nullptr.
        m_pActiveConfiguration.reset();
    }

    return m_pActiveConfiguration;

}
*/
/*
void QLibUsb::Device::TransferEventNotification( QSharedPointer<Transfer> pCompletedTransfer )
{

    // By default: Do nothing.

}
*/

/*
QSharedPointer<QLibUsb::Endpoint> QLibUsb::Device::getControlEndpoint()
{

    return m_pDeviceImpl_->getControlEndpoint();

}
*/


QSharedPointer<libusb_device_descriptor> QLibUsb::Device::getDeviceDescriptor()
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
