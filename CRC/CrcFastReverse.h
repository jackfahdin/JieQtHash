#pragma once
//
//    FILE: CrcFastReverse.h
//  AUTHOR: vovagorodok
// PURPOSE: Arduino class for CRC
//     URL: https://github.com/RobTillaart/CRC

#include <cstdint>
uint8_t reverse8bits(uint8_t in);
uint16_t reverse16bits(uint16_t in);
uint16_t reverse12bits(uint16_t in);
uint32_t reverse32bits(uint32_t in);
uint64_t reverse64bits(uint64_t in);
