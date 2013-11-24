#ifndef USB_H
#define USB_H

#include <QList>
#include <QSharedPointer>

#include "usbimpl.h"

namespace QLibUsb
{
    /// UsbImpl forward declaration
    class UsbImpl;

    class Usb
    {

    public:
        Usb();

        /*!
         * \brief
         *
         * Returns a list of devices (that can be opened) that match the given vendor/product id.
         *
         * \param vendorID (uint16_t): USB-IF vendor id of the desired device.
         * \param deviceID (uint16_t): USB-IF product id of the desired device.
         * \returns (std::list<std::shared_ptr<D>>): List of shared pointers to LibUSB::Device class objects.
         * \sa
         * \note
         * \warning Multiple devices can be returned via this method, if attached.
         */
//        static QList<QSharedPointer<Device> > FindDevice(uint16_t vendorID, uint16_t productID);

        /*!
         * \brief
         *
         * Returns a list of devices (that can be opened) that match the given vendor/product id.
         *
         * \param vendorID (uint16_t): USB-IF vendor id of the desired device.
         * \param deviceID (uint16_t): USB-IF product id of the desired device.
         * \param serialStr (std::wstring): Device unique serial number
         * \returns (std::list<std::shared_ptr<D>>): List of shared pointers to LibUSB::Device class objects.
         * \sa
         * \note
         * \warning Multiple devices can be returned via this method, if attached.
         */
//        static QList<QSharedPointer<Device> > FindDevice(uint16_t vendorID, uint16_t productID, std::wstring serialStr);

        /// Returns all devices attached to the system.
//        static QList<QSharedPointer<Device> > FindAllDevices();

    private:

        friend class TransferImpl;

        static void Initialize();


        /// LibUSBImpl Singleton object
        static QSharedPointer<UsbImpl> Impl_;

    };
};
#endif // USB_H
