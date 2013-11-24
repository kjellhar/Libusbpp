#ifndef USBIMPL_H
#define USBIMPL_H

#include <QSharedPointer>
#include "libusb.h"

namespace QLibUsb
{
    class UsbImpl
    {
    public:
        UsbImpl();

        static QSharedPointer<libusb_context> m_pLibusb_context;
    };
};

#endif // USBIMPL_H
