#include <QCoreApplication>

#include "usb.h"
#include "libusb.h"
#include "device.h"
#include <iostream>

int main(int argc, char *argv[])
{
    uint16_t vendorID = 0x05ac;
    uint16_t productID = 0x8510;

    QCoreApplication a(argc, argv);

    QList<QSharedPointer<QLibUsb::Device> > devices = QLibUsb::Usb::FindAllDevices();

    std::cout << "Finding USB devices \n";

    if (devices.isEmpty()) {
        std::cout << "No USB devices found \n";
    }

    for (int i=0; i<devices.size(); i++)
    {
        std::cout << "Device #" << i
                  << "     vID :  0x"<< std::hex << devices[i]->vendorID()
                  << "     pID :  0x"<< std::hex<< devices[i]->productID()
                  <<"\n";

    }

    return a.exec();
}
