/*
This file is for the implementation of the OLED's Functions
 */

#include "../../system/include/cmsis/cmsis_device.h"
#include "../../system/include/diag/trace.h"
#include "../../system/include/stm32f0-hal/stm32f0xx_hal_spi.h"
#include "../provided_headers/stm32f051x8.h"
#include <stdio.h>

SPI_HandleTypeDef SPI_Handle; // Added for SPI

unsigned char oled_init_cmds[] = {
    0xAE, 0x20, 0x00,        0x40, 0xA0 | 0x01, 0xA8, 0x40 - 1, 0xC0 | 0x08,
    0xD3, 0x00, 0xDA,        0x32, 0xD5,        0x80, 0xD9,     0x22,
    0xDB, 0x30, 0x81,        0xFF, 0xA4,        0xA6, 0xAD,     0x30,
    0x8D, 0x10, 0xAE | 0x01, 0xC0, 0xA0};

unsigned char Characters[][8] = {
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // SPACE
    {0b00000000, 0b00000000, 0b01011111, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // !
    {0b00000000, 0b00000111, 0b00000000, 0b00000111, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // "
    {0b00010100, 0b01111111, 0b00010100, 0b01111111, 0b00010100, 0b00000000,
     0b00000000, 0b00000000}, // #
    {0b00100100, 0b00101010, 0b01111111, 0b00101010, 0b00010010, 0b00000000,
     0b00000000, 0b00000000}, // $
    {0b00100011, 0b00010011, 0b00001000, 0b01100100, 0b01100010, 0b00000000,
     0b00000000, 0b00000000}, // %
    {0b00110110, 0b01001001, 0b01010101, 0b00100010, 0b01010000, 0b00000000,
     0b00000000, 0b00000000}, // &
    {0b00000000, 0b00000101, 0b00000011, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // '
    {0b00000000, 0b00011100, 0b00100010, 0b01000001, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // (
    {0b00000000, 0b01000001, 0b00100010, 0b00011100, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // )
    {0b00010100, 0b00001000, 0b00111110, 0b00001000, 0b00010100, 0b00000000,
     0b00000000, 0b00000000}, // *
    {0b00001000, 0b00001000, 0b00111110, 0b00001000, 0b00001000, 0b00000000,
     0b00000000, 0b00000000}, // +
    {0b00000000, 0b01010000, 0b00110000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // ,
    {0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00001000, 0b00000000,
     0b00000000, 0b00000000}, // -
    {0b00000000, 0b01100000, 0b01100000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // .
    {0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000000,
     0b00000000, 0b00000000}, // /
    {0b00111110, 0b01010001, 0b01001001, 0b01000101, 0b00111110, 0b00000000,
     0b00000000, 0b00000000}, // 0
    {0b00000000, 0b01000010, 0b01111111, 0b01000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // 1
    {0b01000010, 0b01100001, 0b01010001, 0b01001001, 0b01000110, 0b00000000,
     0b00000000, 0b00000000}, // 2
    {0b00100001, 0b01000001, 0b01000101, 0b01001011, 0b00110001, 0b00000000,
     0b00000000, 0b00000000}, // 3
    {0b00011000, 0b00010100, 0b00010010, 0b01111111, 0b00010000, 0b00000000,
     0b00000000, 0b00000000}, // 4
    {0b00100111, 0b01000101, 0b01000101, 0b01000101, 0b00111001, 0b00000000,
     0b00000000, 0b00000000}, // 5
    {0b00111100, 0b01001010, 0b01001001, 0b01001001, 0b00110000, 0b00000000,
     0b00000000, 0b00000000}, // 6
    {0b00000011, 0b00000001, 0b01110001, 0b00001001, 0b00000111, 0b00000000,
     0b00000000, 0b00000000}, // 7
    {0b00110110, 0b01001001, 0b01001001, 0b01001001, 0b00110110, 0b00000000,
     0b00000000, 0b00000000}, // 8
    {0b00000110, 0b01001001, 0b01001001, 0b00101001, 0b00011110, 0b00000000,
     0b00000000, 0b00000000}, // 9
    {0b00000000, 0b00110110, 0b00110110, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // :
    {0b00000000, 0b01010110, 0b00110110, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // ;
    {0b00001000, 0b00010100, 0b00100010, 0b01000001, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // <
    {0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00000000,
     0b00000000, 0b00000000}, // =
    {0b00000000, 0b01000001, 0b00100010, 0b00010100, 0b00001000, 0b00000000,
     0b00000000, 0b00000000}, // >
    {0b00000010, 0b00000001, 0b01010001, 0b00001001, 0b00000110, 0b00000000,
     0b00000000, 0b00000000}, // ?
    {0b00110010, 0b01001001, 0b01111001, 0b01000001, 0b00111110, 0b00000000,
     0b00000000, 0b00000000}, // @
    {0b01111110, 0b00010001, 0b00010001, 0b00010001, 0b01111110, 0b00000000,
     0b00000000, 0b00000000}, // A
    {0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b00110110, 0b00000000,
     0b00000000, 0b00000000}, // B
    {0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b00100010, 0b00000000,
     0b00000000, 0b00000000}, // C
    {0b01111111, 0b01000001, 0b01000001, 0b00100010, 0b00011100, 0b00000000,
     0b00000000, 0b00000000}, // D
    {0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01000001, 0b00000000,
     0b00000000, 0b00000000}, // E
    {0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00000001, 0b00000000,
     0b00000000, 0b00000000}, // F
    {0b00111110, 0b01000001, 0b01001001, 0b01001001, 0b01111010, 0b00000000,
     0b00000000, 0b00000000}, // G
    {0b01111111, 0b00001000, 0b00001000, 0b00001000, 0b01111111, 0b00000000,
     0b00000000, 0b00000000}, // H
    {0b01000000, 0b01000001, 0b01111111, 0b01000001, 0b01000000, 0b00000000,
     0b00000000, 0b00000000}, // I
    {0b00100000, 0b01000000, 0b01000001, 0b00111111, 0b00000001, 0b00000000,
     0b00000000, 0b00000000}, // J
    {0b01111111, 0b00001000, 0b00010100, 0b00100010, 0b01000001, 0b00000000,
     0b00000000, 0b00000000}, // K
    {0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b00000000,
     0b00000000, 0b00000000}, // L
    {0b01111111, 0b00000010, 0b00001100, 0b00000010, 0b01111111, 0b00000000,
     0b00000000, 0b00000000}, // M
    {0b01111111, 0b00000100, 0b00001000, 0b00010000, 0b01111111, 0b00000000,
     0b00000000, 0b00000000}, // N
    {0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b00111110, 0b00000000,
     0b00000000, 0b00000000}, // O
    {0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00000110, 0b00000000,
     0b00000000, 0b00000000}, // P
    {0b00111110, 0b01000001, 0b01010001, 0b00100001, 0b01011110, 0b00000000,
     0b00000000, 0b00000000}, // Q
    {0b01111111, 0b00001001, 0b00011001, 0b00101001, 0b01000110, 0b00000000,
     0b00000000, 0b00000000}, // R
    {0b01000110, 0b01001001, 0b01001001, 0b01001001, 0b00110001, 0b00000000,
     0b00000000, 0b00000000}, // S
    {0b00000001, 0b00000001, 0b01111111, 0b00000001, 0b00000001, 0b00000000,
     0b00000000, 0b00000000}, // T
    {0b00111111, 0b01000000, 0b01000000, 0b01000000, 0b00111111, 0b00000000,
     0b00000000, 0b00000000}, // U
    {0b00011111, 0b00100000, 0b01000000, 0b00100000, 0b00011111, 0b00000000,
     0b00000000, 0b00000000}, // V
    {0b00111111, 0b01000000, 0b00111000, 0b01000000, 0b00111111, 0b00000000,
     0b00000000, 0b00000000}, // W
    {0b01100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011, 0b00000000,
     0b00000000, 0b00000000}, // X
    {0b00000111, 0b00001000, 0b01110000, 0b00001000, 0b00000111, 0b00000000,
     0b00000000, 0b00000000}, // Y
    {0b01100001, 0b01010001, 0b01001001, 0b01000101, 0b01000011, 0b00000000,
     0b00000000, 0b00000000}, // Z
    {0b01111111, 0b01000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // [
    {0b00010101, 0b00010110, 0b01111100, 0b00010110, 0b00010101, 0b00000000,
     0b00000000, 0b00000000}, // back slash
    {0b00000000, 0b00000000, 0b00000000, 0b01000001, 0b01111111, 0b00000000,
     0b00000000, 0b00000000}, // ]
    {0b00000100, 0b00000010, 0b00000001, 0b00000010, 0b00000100, 0b00000000,
     0b00000000, 0b00000000}, // ^
    {0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b00000000,
     0b00000000, 0b00000000}, // _
    {0b00000000, 0b00000001, 0b00000010, 0b00000100, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // `
    {0b00100000, 0b01010100, 0b01010100, 0b01010100, 0b01111000, 0b00000000,
     0b00000000, 0b00000000}, // a
    {0b01111111, 0b01001000, 0b01000100, 0b01000100, 0b00111000, 0b00000000,
     0b00000000, 0b00000000}, // b
    {0b00111000, 0b01000100, 0b01000100, 0b01000100, 0b00100000, 0b00000000,
     0b00000000, 0b00000000}, // c
    {0b00111000, 0b01000100, 0b01000100, 0b01001000, 0b01111111, 0b00000000,
     0b00000000, 0b00000000}, // d
    {0b00111000, 0b01010100, 0b01010100, 0b01010100, 0b00011000, 0b00000000,
     0b00000000, 0b00000000}, // e
    {0b00001000, 0b01111110, 0b00001001, 0b00000001, 0b00000010, 0b00000000,
     0b00000000, 0b00000000}, // f
    {0b00001100, 0b01010010, 0b01010010, 0b01010010, 0b00111110, 0b00000000,
     0b00000000, 0b00000000}, // g
    {0b01111111, 0b00001000, 0b00000100, 0b00000100, 0b01111000, 0b00000000,
     0b00000000, 0b00000000}, // h
    {0b00000000, 0b01000100, 0b01111101, 0b01000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // i
    {0b00100000, 0b01000000, 0b01000100, 0b00111101, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // j
    {0b01111111, 0b00010000, 0b00101000, 0b01000100, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // k
    {0b00000000, 0b01000001, 0b01111111, 0b01000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // l
    {0b01111100, 0b00000100, 0b00011000, 0b00000100, 0b01111000, 0b00000000,
     0b00000000, 0b00000000}, // m
    {0b01111100, 0b00001000, 0b00000100, 0b00000100, 0b01111000, 0b00000000,
     0b00000000, 0b00000000}, // n
    {0b00111000, 0b01000100, 0b01000100, 0b01000100, 0b00111000, 0b00000000,
     0b00000000, 0b00000000}, // o
    {0b01111100, 0b00010100, 0b00010100, 0b00010100, 0b00001000, 0b00000000,
     0b00000000, 0b00000000}, // p
    {0b00001000, 0b00010100, 0b00010100, 0b00011000, 0b01111100, 0b00000000,
     0b00000000, 0b00000000}, // q
    {0b01111100, 0b00001000, 0b00000100, 0b00000100, 0b00001000, 0b00000000,
     0b00000000, 0b00000000}, // r
    {0b01001000, 0b01010100, 0b01010100, 0b01010100, 0b00100000, 0b00000000,
     0b00000000, 0b00000000}, // s
    {0b00000100, 0b00111111, 0b01000100, 0b01000000, 0b00100000, 0b00000000,
     0b00000000, 0b00000000}, // t
    {0b00111100, 0b01000000, 0b01000000, 0b00100000, 0b01111100, 0b00000000,
     0b00000000, 0b00000000}, // u
    {0b00011100, 0b00100000, 0b01000000, 0b00100000, 0b00011100, 0b00000000,
     0b00000000, 0b00000000}, // v
    {0b00111100, 0b01000000, 0b00111000, 0b01000000, 0b00111100, 0b00000000,
     0b00000000, 0b00000000}, // w
    {0b01000100, 0b00101000, 0b00010000, 0b00101000, 0b01000100, 0b00000000,
     0b00000000, 0b00000000}, // x
    {0b00001100, 0b01010000, 0b01010000, 0b01010000, 0b00111100, 0b00000000,
     0b00000000, 0b00000000}, // y
    {0b01000100, 0b01100100, 0b01010100, 0b01001100, 0b01000100, 0b00000000,
     0b00000000, 0b00000000}, // z
    {0b00000000, 0b00001000, 0b00110110, 0b01000001, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // {
    {0b00000000, 0b00000000, 0b01111111, 0b00000000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // |
    {0b00000000, 0b01000001, 0b00110110, 0b00001000, 0b00000000, 0b00000000,
     0b00000000, 0b00000000}, // }
    {0b00001000, 0b00001000, 0b00101010, 0b00011100, 0b00001000, 0b00000000,
     0b00000000, 0b00000000}, // ~
    {0b00001000, 0b00011100, 0b00101010, 0b00001000, 0b00001000, 0b00000000,
     0b00000000, 0b00000000} // <-
};

/* wait function used throughout program to wait for processes to finish */
void wait_ms(int ms) {
  TIM3->CNT = 0x00;
  int end_cycle = ms; // s/1,000ms * 48,000,000cycles/s
  TIM3->CR1 = 0x01;
  while (TIM3->CNT < end_cycle){
	  //trace_printf("WAITING TIM3: %d | End Cycle: %d\n", TIM3->CNT, end_cycle);
  };
  TIM3->CR1 = 0x02;
}

void oled_Write(unsigned char Value) {
  while ((SPI1->SR & 0x02) != 0x2){}; //wait until SPI1 is ready for writing (ie. TXE = 1 in SPI1_SR)
  HAL_SPI_Transmit(&SPI_Handle, &Value, 1, HAL_MAX_DELAY); //send one 8-bit character (also sets BIDIOE=1 in SPI1_CR1)
					  //trace_printf("SPI CR1: %x | CR2: %x \n", SPI1->CR1, SPI1->CR2);
  wait_ms(10);
  while ((SPI1->SR & 0x02) != 0x02); //wait until transmission is complete (TXE = 1 in SPI1_SR) 
  while ((SPI1->SR & 0x80) == 0x80); //wait for busy flag to clear 
}

void oled_Write_Cmd(unsigned char cmd) {
  GPIOB->BSRR = GPIO_BSRR_BS_6; //make PB6 = CS# = 1
  GPIOB->BRR = GPIO_BRR_BR_7; //make PB7 = D/C# = 0 
  GPIOB->BRR = GPIO_BRR_BR_6;   //make PB6 = CS# = 0

  oled_Write(cmd);
  GPIOB->BSRR = GPIO_BSRR_BS_6; //make PB6 = CS# = 1
}

void oled_Write_Data(unsigned char data) {
  GPIOB->BSRR = GPIO_BSRR_BS_6; //make PB6 = CS# = 1
  GPIOB->BSRR = GPIO_BSRR_BS_7; //make PB7 = D/C# = 1
  GPIOB->BRR = GPIO_BRR_BR_6; //make PB6 = CS# = 0

  oled_Write(data);
  
  GPIOB->BSRR = GPIO_BSRR_BS_6; //make PB6 = CS# = 1
}

/*set up oled display*/
void oled_config(void) {
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	/*configure oled with given values*/
	SPI_Handle.Instance = SPI1;
	SPI_Handle.Init.Direction = SPI_DIRECTION_1LINE;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI_Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI_Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
	SPI_Handle.Init.NSS = SPI_NSS_SOFT;
	SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	SPI_Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI_Handle.Init.CRCPolynomial = 7;

	HAL_SPI_Init(&SPI_Handle);
	__HAL_SPI_ENABLE(&SPI_Handle);

  /*Reset LED Display (RES# = PB4):
          - make pin PB4 = 0, wait for a few ms
          - make pin PB4 = 1, wait for a few ms
  */
  GPIOB->BRR = GPIO_BRR_BR_4; //make pin PB4 = 0
  wait_ms(10); 
  GPIOB->BSRR = GPIO_BSRR_BS_4; //make pin PB4 = 1
  wait_ms(10);

  // Send initialization commands to LED Display
  for (unsigned int i = 0; i < sizeof(oled_init_cmds); i++) {
    oled_Write_Cmd(oled_init_cmds[i]);
  }

  /* Fill LED Display data memory (GDDRAM) with zeros:
          - for each PAGE = 0, 1, ..., 7
          set starting SEG = 0
          call oled_Write_Data( 0x00 ) 128 times
  */
  for (int page = 0; page < 8; page++) {
    oled_Write_Cmd(0xB0 | page);
    oled_Write_Cmd(0x00);
    oled_Write_Cmd(0x10);
    for (int i = 0; i < 130; i++) { //when set to less than 130 whole display does not clear. 
      oled_Write_Data(0x00);
    }

  }
}

/*refreshes oled display, called every so often to keep display accurate.*/
void refresh_OLED(float freq) {
  // Buffer size = at most 16 characters per PAGE + terminating '\0'
  unsigned char Buffer[17]; //buffer used for resistance
  unsigned char Buffer2[17]; //buffer used for freqency

  uint32_t tmp = EXTI->IMR; //get the current state of interrupt mask register
  snprintf( Buffer, sizeof(Buffer), "R: %05.0f Ohms\0", ADC1->DR * 1.221); //ADC1->DR holds resistance data multiply by 1.221 to get Ohms

  /* Buffer now contains your character ASCII codes for LED Display
     - select PAGE (LED Display line) and set starting SEG (column)
     - for each c = ASCII code = Buffer[0], Buffer[1], ...,
         send 8 bytes in Characters[c][0-7] to LED Display
  */
	
  oled_Write_Cmd(0xB2); //select page
  oled_Write_Cmd(0x03); //select lower segment
  oled_Write_Cmd(0x10); //select upper segment

  for (int i = 0; i < 17; i++) {
	  tmp = EXTI->IMR; //save the state
	  EXTI->IMR = 0x0000; //disable interrupts
	  //write a character
	  for (int j = 0; j<8; j++){
		  oled_Write_Data(Characters[(int) Buffer[i]][j]);
	  }
	  EXTI->IMR = tmp; //restore state of interrupt mask
  }

  snprintf(Buffer2, sizeof(Buffer2), "F: %05.0f Hz\0", freq);
  /* Buffer2 now contains character ASCII codes for LED Display
     - select PAGE (LED Display line) and set starting SEG (column)
     - for each c = ASCII code = Buffer[0], Buffer[1], ...,
         send 8 bytes in Characters[c][0-7] to LED Display
  */	
  oled_Write_Cmd(0xB4); //select page
  oled_Write_Cmd(0x03); //select lower segment
  oled_Write_Cmd(0x10); //select upper segment
	
    for (int i = 0; i < 17; i++) {
    tmp = EXTI->IMR; //save state
    EXTI->IMR = 0x0000; //disable interrupts
	    //write a character
  	  for (int j = 0; j<8; j++){
  		  oled_Write_Data(Characters[(int) Buffer2[i]][j]);
  	  }
  	  EXTI->IMR = tmp; //restore state
    }

  /* Wait for ~100 ms (for example) to get ~10 frames/sec refresh rate
 - You should use TIM3 to implement this delay (e.g., via polling)
*/
  wait_ms(100);

}
