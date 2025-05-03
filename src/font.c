/**
 * @file font.c
 * @brief Font table data for 5x8 pixel ASCII characters.
 *
 * This source file defines the `font` array, which contains bitmap data
 * for printable ASCII characters ranging from character code 32 (' ') to 126 ('~').
 *
 * Details:
 * - Each character is represented by a 5-byte array.
 * - Each byte defines a vertical column of 8 pixels, where each bit represents a pixel.
 *   - Bit 0 = Top pixel of the column
 *   - Bit 7 = Bottom pixel of the column
 * - The characters are designed for use with pixel-addressable displays (e.g., graphical LCDs or OLEDs).
 * - The font is monospaced (each character occupies 5 columns horizontally).
 *
 * Structure:
 * - `font[95][5]`: A two-dimensional array where:
 *    - 95 = number of printable ASCII characters (from 32 to 126 inclusive)
 *    - 5 = number of bytes (columns) per character
 *
 * Example:
 * - To render 'A' (ASCII 65), use the bitmap stored in `font[65 - 32]`.
 *
 * Notes:
 * - Currently, only a few characters are shown as placeholders. The array should be expanded
 *   with full character definitions for complete functionality.
 * - This file should be paired with display rendering functions that know how to interpret
 *   the 5-column bitmap format.
 */



 #include "font.h"

 // Font array (5x8 pixel font for ASCII 32-126)
 const uint8_t font[95][5] = {
     // 32-126 ASCII characters
     {0x00, 0x00, 0x00, 0x00, 0x00},  // Space character (ASCII 32)
     {0x7E, 0x11, 0x11, 0x11, 0x7E},  // 'A' character (ASCII 65)
 };
 