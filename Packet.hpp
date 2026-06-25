#pragma once
#include <string>
#include <iostream>

// Klasa Bazë Abstrakte (Blueprint)
class Packet
{
protected:
    std::string sourceIP;
    std::string destIP;
    int payloadSize;

public:
    Packet(std::string src, std::string dest, int size)
        : sourceIP(src), destIP(dest), payloadSize(size) {}

    // Destruktori virtual është i detyrueshëm për të pastruar memorien saktë në OOP
    virtual ~Packet() = default;

    // Pure Virtual Functions (Këto e bëjnë klasën Abstrakte)
    virtual void printDetails() const = 0;
    virtual int getPriority() const = 0;
};

// Pako e Zërit (Thirrje VoIP) - Prioritet Shumë i Lartë (10)
class VoicePacket : public Packet
{
public:
    VoicePacket(std::string src, std::string dest, int size) : Packet(src, dest, size) {}

    void printDetails() const override
    {
        std::cout << "[VOICE/VoIP] " << sourceIP << " -> " << destIP
                  << " | Size: " << payloadSize << " bytes | Priority: URGENT\n";
    }

    int getPriority() const override { return 10; }
};

// Pako e të Dhënave (Web/File) - Prioritet Normal (1)
class DataPacket : public Packet
{
public:
    DataPacket(std::string src, std::string dest, int size) : Packet(src, dest, size) {}

    void printDetails() const override
    {
        std::cout << "[DATA/FILE]  " << sourceIP << " -> " << destIP
                  << " | Size: " << payloadSize << " bytes | Priority: NORMAL\n";
    }

    int getPriority() const override { return 1; }
};
