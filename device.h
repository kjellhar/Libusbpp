#ifndef DEVICE_H
#define DEVICE_H

#include <QSharedPointer>
#include <QString>

#include "libusb.h"

namespace QLibUsb
{

    class DeviceDeleter
    {
    public:
        void operator()(libusb_device* dev) { libusb_unref_device(dev); };

    };

    class DeviceHandleDeleter
    {
    public:
        void operator()(libusb_device_handle* devhandle) { libusb_close(devhandle); };

    };

    /// Libusb Device Implementation Forward Declaration
    class DeviceImpl;

    class Device
    {
    public:
        Device(libusb_device* pDevice);


    // Device State

        /// Returns TRUE if the device is open.
        bool isOpen();

        /// Opens the device.
        void Open();

    // Device Descriptor

        /// USB specification release number
        uint16_t USBSpecification();

        /// USB-IF class code
        uint8_t DeviceClass();

        /// USB-IF subclass code for the device, qualified by the bDeviceClass value.
        uint8_t DeviceSubclass();

        /// USB-IF protocol code for the device, qualified by the bDeviceClass and bDeviceSubClass values.
        uint8_t DeviceProtocol();

        /// USB-IF vendor ID
        uint16_t vendorID();

        /// USB-IF product ID
        uint16_t productID();

        /// Returns a string describing the product.
        QString ProductString();

        /// Returns a string describing the manufacturer.
        QString ManufacturerString();

        /// Returns the serial number string of the device.
        QString SerialString();

        /// Returns the number of possible configurations for this device.
        uint8_t NumConfigurations();

    // Configurations

        /// Returns the requested configuration
//        QSharedPointer<Configuration> getConfiguration(uint8_t ConfigValue);

        /// Returns the activeConfiguration
//        QSharedPointer<Configuration> getActiveConfiguration();

    // Control endpoint

        /// Returns the control endpoint (Endpoint 0)
//        QSharedPointer<Endpoint> getControlEndpoint();


        QSharedPointer<libusb_device_descriptor> getDeviceDescriptor();

    protected:

        /// Transfers need access to the transfer event notification method of their target device.
        friend class TransferImpl;

        /// Notification of a completed transfer
        /// \warning This function can be called from other threads when using asynchronous transfers!
//        virtual void TransferEventNotification(QSharedPointer<Transfer> pCompletedTransfer);


    private:

        /// Cached Active Configuration
//        QSharedPointer<Configuration> m_pActiveConfiguration;

        /// Device Descriptor
        QSharedPointer<libusb_device_descriptor> m_pDeviceDescriptor;

        /// Device object
        QSharedPointer<libusb_device> m_pDevice;

        /// Device handle
        QSharedPointer<libusb_device_handle> m_pHandle;
    };
};

#endif // DEVICE_H
