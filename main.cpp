#include "Router.hpp"
#include <iostream>
#include <memory>
#include <limits>

void showMenu()
{
    std::cout << "\n>>> ERICSSON NETWORK NODE SIMULATOR <<<\n";
    std::cout << "1. Simulate VoIP Call (Voice Packet)\n";
    std::cout << "2. Simulate File Download (Data Packet)\n";
    std::cout << "3. Check Buffer Queue Size\n";
    std::cout << "4. Process Network Traffic (Routing)\n";
    std::cout << "5. Exit Simulator\n";
    std::cout << "Select Operation: ";
}

int main()
{
    Router telecomRouter;
    int choice;

    while (true)
    {
        showMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 5)
        {
            std::cout << "\nNode shutting down gracefully...\n";
            break;
        }

        switch (choice)
        {
        case 1:
        {
            std::string src, dest;
            std::cout << "Source IP: ";
            std::cin >> src;
            std::cout << "Destination IP: ";
            std::cin >> dest;
            // std::make_unique mbron memorien
            telecomRouter.receivePacket(std::make_unique<VoicePacket>(src, dest, 128));
            std::cout << "[+] Voice packet buffered.\n";
            break;
        }
        case 2:
        {
            std::string src, dest;
            int size;
            std::cout << "Source IP: ";
            std::cin >> src;
            std::cout << "Destination IP: ";
            std::cin >> dest;
            std::cout << "Payload Size (bytes): ";
            std::cin >> size;
            telecomRouter.receivePacket(std::make_unique<DataPacket>(src, dest, size));
            std::cout << "[+] Data packet buffered.\n";
            break;
        }
        case 3:
            std::cout << "Packets currently in buffer: " << telecomRouter.getPendingCount() << "\n";
            break;
        case 4:
            telecomRouter.processTraffic();
            break;
        default:
            std::cout << "Invalid operation code.\n";
        }
    }
    return 0;
}
