#include "usbimpl.h"

/// Used by shared_ptr to delete a libusb context
class ContextDeleter
{
public:
    void operator()(libusb_context* ctx) { libusb_exit(ctx); };

};

QLibUsb::UsbImpl::UsbImpl()
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
QSharedPointer<libusb_context> QLibUsb::UsbImpl::m_pLibusb_context;
