#pragma once
#include "Packet.hpp"
#include <queue>
#include <memory>
#include <vector>

// Ky "Strukturë Krahasuese" e mëson radhën (Queue) se kush ka prioritet më të madh
struct PacketCompare
{
    bool operator()(const std::unique_ptr<Packet> &a, const std::unique_ptr<Packet> &b) const
    {
        return a->getPriority() < b->getPriority();
    }
};

class Router
{
private:
    // Priority Queue që mban Smart Pointers (Shumë e avancuar për një CV Junior)
    std::priority_queue<std::unique_ptr<Packet>, std::vector<std::unique_ptr<Packet>>, PacketCompare> buffer;
    int totalProcessed = 0;

public:
    // Pranojmë pakon. Përdorim std::move() për performancë maksimale (Zero-copy overhead)
    void receivePacket(std::unique_ptr<Packet> pkt)
    {
        buffer.push(std::move(pkt));
    }

    // Proceso pakot duke respektuar QoS (Thirrjet dalin të parat)
    void processTraffic()
    {
        std::cout << "\n=== STARTING NETWORK ROUTING ===\n";
        if (buffer.empty())
        {
            std::cout << "No packets in the buffer queue.\n";
            return;
        }

        while (!buffer.empty())
        {
            // Lexojmë pakon nga fillimi i radhës
            const auto &currentPacket = buffer.top();

            // Ekzekutojmë funksionin përkatës pavarësisht a është Voice apo Data
            currentPacket->printDetails();

            // E heqim nga radha (memorja fshihet automatikisht falë unique_ptr)
            buffer.pop();
            totalProcessed++;
        }
        std::cout << "================================\n";
        std::cout << "Total Packets Routed: " << totalProcessed << "\n";
    }

    int getPendingCount() const { return buffer.size(); }
};
