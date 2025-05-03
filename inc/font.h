/**
 * @file font.h
 * @brief Font table definition for 5x8 pixel characters.
 *
 * This header file declares an external font table used for rendering simple ASCII characters
 * in a 5x8 pixel format. Each character is represented by a 5-byte array, where each byte
 * defines a vertical column of 8 pixels.
 *
 * Details:
 * - The table contains 95 printable ASCII characters, corresponding to character codes 32 (' ') to 126 ('~').
 * - Each character is defined as a 5-column bitmap, intended for displays that use monospaced fonts.
 * - The font array is typically used for basic text rendering on graphic LCDs, OLEDs, or other pixel-addressable displays.
 *
 * Definitions:
 * - `font[95][5]`: 2D array where each entry holds 5 bytes of column data for one character.
 *
 * Usage:
 * - To render a character, lookup `font[ascii_code - 32]` and draw each column sequentially.
 * - Assumes top-to-bottom bit ordering for each byte (bit 0 = top pixel, bit 7 = bottom pixel).
 *
 * Dependencies:
 * - None directly; implementation-specific use will depend on the display driver code.
 */



 #ifndef __FONT_H
 #define __FONT_H
 
 // Simple 5x8 characters
 extern const uint8_t font[95][5];
 
 #endif /* __FONT_H */
 