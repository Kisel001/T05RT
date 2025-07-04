/***************************************************************
 * Copyright (C) 1992-1999
 *    Galinsky Software
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : TGAHEAD.H
 * PURPOSE     : TGA (TrueVisionTargaGraphicsAdapter) image file
 *               format.
 *               File header/footer structures.
 * PROGRAMMER  : Vitaly A. Galinsky.
 * LAST UPDATE : 03.03.1999
 * NOTE        : Module prefix 'TGA'.
 *
 * No part of this file may be changed without agreement of
 * Vitaly A. Galinsky personally and Computer Graphics Support
 * Group of 30 Phys-Math Gymnasium.
 */

#ifndef _TGAHEAD_H_
#define _TGAHEAD_H_

#include <commondf.h>

/***
 * TGA file structure:
 *   FileHeader.
 *   IDString.
 *   ColorMap (palette table).
 *   Image data.
 *  TGA v.2-00:
 *   Extensions data.
 *   FileFooter.
 ***/

/* Base image header, TGA v.1-00, placed at file begin */
typedef struct tagtgaFILEHEADER
{
  BYTE IDLength;     /* Length of ID string placed after header */
  BYTE ColorMapType; /* 1 - for color-mapped images */

  /* Image type:
   *   0 - no image
   *   1 - Uncompressed color-mapped image
   *   2 - Uncompressed RGB image
   *   3 - Uncompressed black-white image
   *   9 - Runlength encoded color-mapped image
   *  10 - Runlength encoded RGB image
   *  11 - Compressed black-white image
   *  32 - Compressed color-mapped image (Huffman, Delta, RLE)
   *  33 - Compressed color-mapped image (Huffman, Delta, RLE,
   *       4-pass quadtree-type process)
   */
  BYTE ImageType;

  /* Color-map (palette) data (ignored if 'ColorMapType' == 0) */
  WORD PaletteStart; /* First palette table (color-map) entry index */
  WORD PaletteSize;  /* Length of palette table in entries */
  BYTE PaletteEntrySize;  /* Length of palette table entry in bytes */

  /* Image data */
  WORD X, Y; /* Image origin (lower-left corner) coordinates */
  WORD Width, Height; /* Image size (in pixels) */
  BYTE BitsPerPixel; /* Pixel size in bits */

  /* Image description (by bits):
   *   bits 3-0   - amount of attributes bits for every pixel
   *   bits 4     - reserved (must be 0)
   *   bits 5     - screen origin: 0 - lower-left, 1 - upper-left
   *   bits 7-6   - data storage interleaving:
   *                  00 = non-interleaved
   *                  01 = two-way (even/odd) interleaving
   *                  10 = four way interleaving
   *                  11 = reserved
   */
  BYTE ImageDescr;

  /* After this header place ID string (length IDLength bytes),
   * than color-map table, than image data.
   * RLE compression format: <byte> <data>
   *    7 6 5 4 3 2 1 0 |
   *   '_'_'_'_'_'_'_'_'|d.a.t.a.
   *    ^ +-----------+ <- (repeat - 1) = [1..128]
   *    |
   *    +- if 1 than next data repeated color
   *       otherwise - next 'repeat' times color data is
   *       unpacked pixels
   */
} tgaFILEHEADER;

/* Footer TGA 2.00 identify string */
#define TGA_EXT_SIGNATURE "TRUEVISION-XFILE."

/* Image footer, TGA v.2-00, placed at end of file */
typedef struct tagtgaFILEFOOTER
{
  /* Extension area offset from file begin (0 - absent) */
  DWORD ExtensionOffset;
  /* Developer area offset from file begin (0 - absent) */
  DWORD DeveloperOffset;
  /* Signature of TGA - "TRUEVISION-XFILE.\x00",
   * see TGA_EXT_SIGNATURE */
  CHAR Signature[18];
} tgaFILEFOOTER;

/* Extension header */
typedef struct tagtgaEXTHEADER
{
  WORD Size;               /* Extension area size */
  CHAR AuthorName[41];     /* Author name */
  /* Author comments: 4 lines by 80 characters with NULLs */
  CHAR AuthorComment[324];
  /* Date/time of last file modification */
  WORD
    StampMonth, StampDay, StampYear,
    StampHour, StampMinute, StampSecond;
  CHAR JobName[41];        /* Name/ID of task, job */
  /* Job time */
  WORD
    JobHour, JobMinute, JobSecond;
  CHAR SoftwareID[41];     /* Software ID */
  WORD VersionNumber;      /* Software version number (* 100) */
  BYTE VersionLetter;      /* Software version letter */
  DWORD KeyColor;          /* Key, background color */
  /* Aspect ration Num./Denom. */
  WORD
    PixelNumerator, PixelDenominator;
  /* Gamma correction Num./Denom. */
  WORD
    GammaNumerator, GammaDenominator;
  /* Offset of color correction table:
   *   WORD Alpha, Red, Green, Blue;    x 256 (2048 bytes)
   *  black - 0, 0, 0, 0; white - 65535, 65535, 65535, 65535 */
  DWORD ColorOffset;
  /* Offset of stamp image: 2 bytes WxH, stamp data (the same
   * to image format, no compressed) */
  DWORD StampOffset;
  /* Offset of raster lines table: 4 bytes offset for every line */
  DWORD ScanOffset;
  /* Type of attributes: 0 - no alpha present */
  BYTE AttributeType;
} tgaEXTHEADER;

#endif /* _TGAHEAD_H_ */

/* END OF 'TGAHEAD.H' FILE */

