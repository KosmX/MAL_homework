//
// Created by kosmx on 2023-05-27.
//

#ifndef MAL_HOMEWORK_PACKETS_H
#define MAL_HOMEWORK_PACKETS_H
#ifdef __cplusplus

#include <string>
#include <cstdint>


class UartPacket {
public:
    virtual void write() = 0;
};

class StringMsg : UartPacket {
public:
    StringMsg(const std::string& str) : str{str} {}
    void write() override;
private:
    const std::string& str;
};

class FreqPacket : UartPacket {
public:
    explicit FreqPacket(float frequency) : freq{frequency} {}
    void write() override;
private:
    float freq;
};


#endif
#endif //MAL_HOMEWORK_PACKETS_H
