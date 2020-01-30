#ifndef BITMAPS_H
#define BITMAPS_H

const uint8_t PROGMEM logo[] =
{
    34, 24, // width,height
    0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0xe0, 0xfe, 0xff, 0xe3, 0xe3, 0xe3,
    0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xff, 0xfe, 0xe0,
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x0c, 0xfd, 0x0d, 0x0d,
    0x01, 0xfd, 0xc5, 0xc5, 0xfd, 0x01, 0xfd, 0xc5,
    0xc5, 0xfd, 0x01, 0xfd, 0xc1, 0xc1, 0xc1, 0x01,
    0xfd, 0xd5, 0xdd, 0xf1, 0x01, 0xfd, 0xc5, 0xc5,
    0xfd, 0x01, 0xed, 0x31, 0x31, 0xdc,
};


const uint8_t PROGMEM titles[] =
{
    48, 8, // width,height

    // Frame 0 - Move Mouse
    0x7e, 0x06, 0x1e, 0x06, 0x7e, 0x00, 0x7e, 0x62,
    0x62, 0x7e, 0x00, 0x3e, 0x40, 0x7e, 0x3e, 0x00,
    0x7e, 0x6a, 0x6a, 0x62, 0x00, 0x00, 0x00, 0x7e,
    0x06, 0x1e, 0x06, 0x7e, 0x00, 0x7e, 0x62, 0x62,
    0x7e, 0x00, 0x7e, 0x60, 0x60, 0x7e, 0x00, 0x5e,
    0x56, 0x56, 0x76, 0x00, 0x7e, 0x6a, 0x6a, 0x62,

    // Frame 1 - Click Mouse
    0x00, 0x00, 0x7e, 0x1a, 0x1a, 0x7e, 0x00, 0x7e,
    0x60, 0x60, 0x7e, 0x00, 0x06, 0x7e, 0x06, 0x06,
    0x00, 0x7e, 0x62, 0x62, 0x7e, 0x00, 0x7e, 0x62,
    0x62, 0x62, 0x00, 0x7e, 0x60, 0x60, 0x60, 0x00,
    0x62, 0x7e, 0x62, 0x62, 0x00, 0x7e, 0x62, 0x62,
    0x62, 0x00, 0x7e, 0x18, 0x76, 0x76, 0x00, 0x00,

    // Frame 2 - Roll Dice
    0x00, 0x00, 0x00, 0x7e, 0x1a, 0x7a, 0x5e, 0x00,
    0x7e, 0x62, 0x62, 0x7e, 0x00, 0x7e, 0x60, 0x60,
    0x60, 0x00, 0x7e, 0x60, 0x60, 0x60, 0x00, 0x00,
    0x00, 0x7e, 0x62, 0x64, 0x78, 0x00, 0x62, 0x7e,
    0x62, 0x62, 0x00, 0x7e, 0x62, 0x62, 0x62, 0x00,
    0x7e, 0x6a, 0x6a, 0x62, 0x00, 0x00, 0x00, 0x00,
};


#endif
