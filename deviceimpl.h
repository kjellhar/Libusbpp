#ifndef DEVICEIMPL_H
#define DEVICEIMPL_H

#include <QSharedPointer>
#include <QWeakPointer>
#include <QString>

#include "libusb.h"
#include "device.h"

namespace QLibUsb
{

    class Device;

/*    class DeviceDeleter
    {
    public:
        void operator()(libusb_device* dev) { libusb_unref_device(dev); };

    };

    class DeviceHandleDeleter
    {
    public:
        void operator()(libusb_device_handle* devhandle) { libusb_close(devhandle); };

    };
*/
    class DeviceImpl
    {
    public:
        DeviceImpl(libusb_device* pDevice);


        /// Obtains the device descriptor.
        QSharedPointer<libusb_device_descriptor> getDeviceDescriptor();

        /// Returns TRUE if the device is open
        bool isOpen()const;

        /// Opens a handle to the usb device.
        void Open();

        /// Obtains the language id
        uint16_t getLangId();

        /// Obtains the given ascii descriptor string
        QString getStringDescriptor(uint8_t index);

        /// Returns the index of the active configuration.
        bool getActiveConfiguration( uint8_t &index )const;

        /// Sets the active configuration
        void setActiveConfiguration( uint8_t index );

        /// Returns the requested the configuration descriptor.
//        QSharedPointer<Configuration> getConfiguration(uint8_t ConfigValue);

        /// Device object
        QSharedPointer<libusb_device> m_pDevice;

        /// Device handle
        QSharedPointer<libusb_device_handle> m_pHandle;


        /// Returns the LibUSB++ device object/owner
        QWeakPointer<Device> getDevice()const;

        /// Allows device to set the parent device after initial construction.
        void setParentDevice(QWeakPointer<Device> pParentDevice);

        /// Returns endpoint 0
//        QSharedPointer<Endpoint> getControlEndpoint();

    private:


        /// Weak_ptr collection of other configuration objects.
//        std::map<uint8_t, QWeakPointer<Configuration>> m_ConfigurationMap;

        /// Device Descriptor
        QSharedPointer<libusb_device_descriptor> m_pDeviceDescriptor;

        /// Libusb++ device/parent
        QWeakPointer<Device> m_ParentDevice;

        /// Language ID
        uint16_t languageId;

        /// Dummy descriptor for Endpoint zero.
        libusb_endpoint_descriptor m_EndpointZeroDescriptor;

//        QSharedPointer<Endpoint> m_pEndpointZero;

    };
};

#endif // DEVICEIMPL_H
