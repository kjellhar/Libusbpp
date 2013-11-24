#include <QList>
#include <QSharedPointer>
#include <QString>
#include <iostream>

#include "usb.h"
#include "device.h"

/// Used by shared_ptr to delete a libusb context
class ContextDeleter
{
public:
    void operator()(libusb_context* ctx) { libusb_exit(ctx); };

};


QLibUsb::Usb::Usb()
{
}




QList<QSharedPointer<QLibUsb::Device> > QLibUsb::Usb::FindDevice( uint16_t vendorID, uint16_t productID)
{

    // Ensure libusb is initialized.
    Initialize();

    // Create a list of attached devices
    libusb_device **device_list = 0;

    ssize_t NumResults = libusb_get_device_list(m_pLibusb_context.data(), &device_list);

    // Iterate each device.
    QList<QSharedPointer<Device> > deviceList;

    for (ssize_t i = 0; i < NumResults; i++)
    {
        // Create a device.
        QSharedPointer<Device> pDevice;
        pDevice.reset(new Device(device_list[i]));

        // Check the device
        if ((pDevice->vendorID() == vendorID) && (pDevice->productID() == productID))
        {
            // Add device to the output list
            deviceList.push_back(pDevice);
        }
std::cout << "f \n";
    }

    // Free the device list
    libusb_free_device_list(device_list, 1);

    return deviceList;

}





QList<QSharedPointer<QLibUsb::Device> > QLibUsb::Usb::FindDevice( uint16_t vendorID, uint16_t productID, QString serialStr)
{

    // Get list of devices that match product/vendor id.
    QList<QSharedPointer<Device> > DeviceList = FindDevice(vendorID, productID);

    QList<QSharedPointer<Device> > ResultList;

    // Open each device and locate a matching serial.
    for (int i = 0; i < DeviceList.size(); ++i)
    {
        if(DeviceList.at(i)->SerialString() == serialStr)
        {

            ResultList.push_back(DeviceList[i]);
            break;
        }
    }

    return ResultList;
}




QList<QSharedPointer<QLibUsb::Device> > QLibUsb::Usb::FindAllDevices( )
{

    // Ensure libusb is initialized.
    Initialize();

    // Create a list of attached devices
    libusb_device **device_list = 0;

    ssize_t NumResults = libusb_get_device_list(m_pLibusb_context.data(), &device_list);


    // Iterate each device.
    QList<QSharedPointer<Device> > deviceList;

    for (ssize_t i = 0; i < NumResults; i++)
    {

        // Create a device.
        QSharedPointer<Device> pDevice;

        pDevice.reset(new Device(device_list[i]));

        // Add device to the output list
        deviceList.push_back(pDevice);

    }

    // Free the device list
    libusb_free_device_list(device_list, 1);

    return deviceList;

}



void QLibUsb::Usb::Initialize()
{
    // Ensure libusb is initialized.
    if (m_pLibusb_context.isNull())
    {
        // Create the libusb context
        libusb_context* pContext = 0;
        int Result = libusb_init(&pContext);
        if (Result != LIBUSB_SUCCESS)
        {
            //throw std::exception("libusb_init() failed.");
        }

        // Store in a shared_ptr
        m_pLibusb_context.reset(pContext, ContextDeleter());
    }

}

QSharedPointer<libusb_context> QLibUsb::Usb::m_pLibusb_context;
