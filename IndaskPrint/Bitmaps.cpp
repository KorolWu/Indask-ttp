/* Bitmaps.cpp
 *
 * Copyright (c) 2007-2011, The Technology Partnership Plc
 */

// Utility functions for opening bitmap files and converting to Meteor image commands

#include "stdafx.h"

// Standard libraries
#include <stdio.h>

// Image handling libraries
#include <atlimage.h>			// For bitmap handling
#include <QDebug>

// Meteor specific includes
#include "PrinterInterface.h"	// Contains definitions for all the Meteor library functions
#include "Meteor.h"				// Definition of common datatypes and constants
#include "typedef.h"

#include "Bitmaps.h"

uint32* Make_1BPP_Bitmap(const _TCHAR* filename);
uint32* Make_2BPP_Bitmap(const _TCHAR* filename);
uint32* Make_4BPP_Bitmap(const _TCHAR* filename);
uint32* DrawBitmap(CImage& oBmp, DWORD trueBpp);

//---------------------------------------------------------------------------
/**
    Check the head type, and make an appropriate bitmap.
    
    Different head types require different image formats, as
    they have differing numbers of greyscale levels.

    The mapping from the bitmap's RGB value to 1,2 or 4 bits per pixel 
    greyscale in this sample code is general purpose and entirely arbitrary; in 
    a real application the print data is typically processed using RIP software 
    so should already be at the correct bit depth by this point.

    Also note that print head types which accept 4 bit-per-pixel print data
    only use the least significant 3 bits of each pixel for printing; the most 
    significant bit should be zero.

    @param  filename image file path
    @return pointer to the image to be sent to PrintEngine or NULL if something went wrong
*/
uint32* MakeBitmap(const _TCHAR* filename) {

    const TAppStatus* pStatus = PiGetPrnStatus();
    if(!pStatus) {
        qDebug()<<"Error: Unable to read head type from Printer Interface\n";
        return nullptr;
    }

    //-- validate head type
    switch(pStatus->HeadType) {

    case HT_LEOPARD:    //  = 0x00000001,   // Leopard/Xaar Omnidot318/TTEC CA3/CA4/CE2 etc.
    case HT_SPECTRA:    //  = 0x00000002,   // Spectra Nova/Galaxy/S-Class
    case HT_HSS:        //  = 0x00000003,   // Xaar 1001 (HSS)
    case HT_KJ4:        //  = 0x00000004,   // Kyocera KJ4
    case HT_XJ500:      //  = 0x00000005,   // Xaar XJ 500
    case HT_QCLASS:     //  = 0x00000006,   // Dimatix Q-Class
    case HT_POLARIS:    //  = 0x00000007,   // Polaris
    case HT_CF1:        //  = 0x00000008,   // TTEC CF1
    case HT_SPT_508GS:  //  = 0x00000009,   // Seiko 508 greyscale
    case HT_RG4:        //  = 0x0000000A,   // Ricoh GEN4
    case HT_RG5:        //  = 0x0000000B,   // Ricoh GEN5
    case HT_LEXMARK:    //  = 0x0000000C,   // Lexmark (Yellowstone)
    case HT_SPT_254GS:  //  = 0x0000000D,   // Seiko 254 greyscale
    case HT_SPT_510BIN: //  = 0x0000000E,   // Seiko 510 binary
    case HT_VISTA:      //  = 0x0000000F,   // Vista
    case HT_STARFIRE:   //  = 0x00000010,   // Dimatix Starfire   
    case HT_SPT_RC512:  //  = 0x00000012,   // SII Printek RC512
    case HT_K1200:      //  = 0x00000014,   // 1200DPI Kyocera KJ4
    case HT_SPT_RC1536: //  = 0x00000015,   // SII Printek RC1536
    case HT_K300:       //  = 0x00000016,   // 300DPI Kyocera KJ4    
    case HT_K600:       //  = 0x00000018,   // 600DPI Kyocera KJ4
    case HT_SPT_1024GS: //  = 0x00000019,   // SII Printek 1024GS
    case HT_4CF1:       //  = 0x0000001A,   // TTEC CF1, 4 heads mount
    case HT_SAMBA:      //  = 0x0000001B,   // Dimatix Fujifilm Samba head
    case HT_GH2220:     //  = 0x0000001C,   // Ricoh GH2220
    //case HT_KM160:      //  = 0x0000001D,   // Konica Minolta MC160H and ML160H 600DPI MEMS heads
    case HT_KM130:      //  = 0x0000001E,   // Konica Minolta ME130H 1200DPI MEMS head
    case HT_KM1800I:    //  = 0x0000001F,   // Konica Minolta KM1800i head
    case HT_KM1024I:    //  = 0x00000020,   // Konica Minolta KM1024iMAE, KM1024iMAE, KM1024iMHE, KM1024iSHE  heads
    case HT_K150:       //  = 0x00000021,   // 150DPI Kyocera KJ4 (four colour head)   
        break;
   
    default:
        qDebug()<<"Unsupported head type:%d\n"<< pStatus->HeadType;
        return nullptr;
    }


    //-- create image depending on BPP for the head type
    //-- the bits per pixel setting is specified in the Meteor configuration file; it 
    //   can also be changed by the application using PiSetParam
    switch(pStatus->BitsPerPixel) {
    case 1:
        return Make_1BPP_Bitmap(filename);
    case 2:
        return Make_2BPP_Bitmap(filename);
    case 4:
        return Make_4BPP_Bitmap(filename);
    default:
        printf("Unsupported BPP value:%d\n", pStatus->BitsPerPixel);
        return nullptr;
    }


}

//---------------------------------------------------------------------------
/**
    Creates 1 Bit per pixel bitmap from the given image file on a disk.
    The caller is responsible for freeing the buffer this that function allocates.

    @param  filename image file path
    @return pointer to the image to be sent to PrintEngine or NULL if something went wrong
*/
uint32* Make_1BPP_Bitmap(const _TCHAR* filename) {
    // Colour table.
    const RGBQUAD tab[2] = {
        {0,0,0,0}, {255, 255, 255, 0}
    };

    CImage oBmp;
    HRESULT hRes = oBmp.Load(filename);
    if (S_OK == hRes) {
        CImage oOneBit;						// Construct the CImage
        oOneBit.Create(oBmp.GetWidth(), oBmp.GetHeight(), 1); // Create and attach a bitmap
        oOneBit.SetColorTable(0, 2, tab);		// Set the colour table
        oBmp.BitBlt(oOneBit.GetDC(), 0, 0, SRCCOPY); // Copy the bitmap
        oOneBit.ReleaseDC();					// Done with DC

        return (DrawBitmap(oOneBit,1));		// Draw bitmap for printer
    }

    return nullptr;
}

//---------------------------------------------------------------------------
/**
    Creates 2 Bits per pixel bitmap from the given image file on a disk.
    The caller is responsible for freeing the buffer this that function allocates.

    @param  filename image file path
    @return pointer to the image to be sent to PrintEngine or NULL if something went wrong
*/
uint32* Make_2BPP_Bitmap(const _TCHAR* filename) {
    // Colour table. Repeats four times (QClass has only 4 grey levels)
    const RGBQUAD tab[16] = {
        {0,0,0,0},       {85,85,85,0},    {170,170,170,0},    {255,255,255,0},
        {0,0,0,0},       {85,85,85,0},    {170,170,170,0},    {255,255,255,0},
        {0,0,0,0},       {85,85,85,0},    {170,170,170,0},    {255,255,255,0},
        {0,0,0,0},       {85,85,85,0},    {170,170,170,0},    {255,255,255,0},
    };

    CImage oBmp;
    HRESULT hRes = oBmp.Load(filename);
    if (S_OK == hRes) {
        CImage oFourBit;						// Construct the CImage
        oFourBit.Create(oBmp.GetWidth(), oBmp.GetHeight(), 4); // Create and attach a bitmap
        oFourBit.SetColorTable(0, 16, tab);		// Set the colour table
        oBmp.BitBlt(oFourBit.GetDC(), 0, 0, SRCCOPY); // Copy the bitmap
        oFourBit.ReleaseDC();					// Done with DC

        return (DrawBitmap(oFourBit,2));		// Draw bitmap for printer
    } else {
        printf("Error, unable to open input file: \"%S\"\n",filename);
    }
    return NULL;
}

//---------------------------------------------------------------------------
/**
        从磁盘上的给定图像文件创建每像素4位 位图。
        调用方负责释放此函数分配的缓冲区。

    @param  filename image file path
    @return pointer to the image to be sent to PrintEngine or NULL if something went wrong
*/
uint32* Make_4BPP_Bitmap(const _TCHAR* filename) {
    // Colour table. Repeats twice (Leopard has only 8 grey levels)
    const RGBQUAD tab[16] = {
        {0,0,0,0},       {36,36,36,0},    {72,72,72,0},    {108,108,108,0},
        {144,144,144,0}, {180,180,180,0}, {216,216,216,0}, {255, 255, 255, 0},
        {0,0,0,0},       {36,36,36,0},    {72,72,72,0},    {108,108,108,0},
        {144,144,144,0}, {180,180,180,0}, {216,216,216,0}, {255, 255, 255, 0}
    };

    CImage oBmp;
    HRESULT hRes = oBmp.Load(filename);
    if (S_OK == hRes) {
        CImage oFourBit;						// Construct the CImage
        oFourBit.Create(oBmp.GetWidth(), oBmp.GetHeight(), 4); // Create and attach a bitmap
        oFourBit.SetColorTable(0, 16, tab);		// Set the colour table
        oBmp.BitBlt(oFourBit.GetDC(), 0, 0, SRCCOPY); // Copy the bitmap
        oFourBit.ReleaseDC();					// Done with DC

        return (DrawBitmap(oFourBit,3));		// Draw bitmap for printer
    } else {
        printf("Error, unable to open input file: \"%S\"\n",filename);
    }
    return NULL;
}

//---------------------------------------------------------------------------
/*
* DrawBitmap extracts the colour plane from the supplied bitmap, formatting it
* for passing to the Printer Interface, the format is as defined in the Meteor user manual,
* see PCMD_IMAGE for details.
* This function mallocs memory which is never freed.  A proper application needs to be careful
* to free this memory correctly.

DrawBitmap从提供的位图中提取颜色平面，并对其进行格式化
要传递到打印机界面，格式如Meteor用户手册中所定义，
有关详细信息，请参见PCMD_图像。
此函数会占用从未释放的内存。正确的应用需要小心
要正确释放此内存。*/
uint32* DrawBitmap(CImage& oBmp, DWORD trueBpp) {

    const uint32 MSB32 = 0x80000000;

    uint32* pBuff = NULL;
    DWORD imagebpp, outbpp;

    DWORD x, y, w, mask, shift, isize, width, height, byteoff;
    uint32* dp;
    uint8 b;
    uint8* lbuff;
    DWORD srcMask;
    DWORD bppMask;

    imagebpp = oBmp.GetBPP();					// Get image bits-per-pixel (1 or 4)
    outbpp = (trueBpp == 3) ? 4 : trueBpp;
    width = oBmp.GetWidth();
    height = oBmp.GetHeight();
    isize = ((width * outbpp + 31) >> 5) * height;
    pBuff = (uint32*) malloc(sizeof(uint32) * (isize + 6));      // Room for image + header
    if (!pBuff) {
        printf("Out of memory");
        return NULL;
    }

    // oBmp.Save(L"c:\\temp\\meteor_test.bmp");			// For checking

    memset(pBuff, 0, (isize + 6) * sizeof(DWORD));		// Clear out the buffer

    // Setup the header at the start of the buffer
    pBuff[0] = PCMD_IMAGE;                              // Command
    pBuff[1] = isize + 4;                               // Dword count
    pBuff[2] = 1;	  									// Plane
    pBuff[3] = 1;		                                // Xleft
    pBuff[4] = 0;                                       // Ytop
    pBuff[5] = width;			                        // Width

    // Now write the bitmap to the buffer
    dp = &pBuff[6];                                     // First data

    // Conversion used depends on the number of bits per pixel.  This is determined by the
    // head type used, and how many greyscale levels are available.

    if (trueBpp == 1) {
        // All binary heads, e.g. Spectra heads
        for (y = 0 ; y < height ; y++) {
            lbuff = (uint8 *)oBmp.GetPixelAddress(0, y);
            w = 0;
            mask = MSB32;
            srcMask = 0x80;
            for (x = 0 ; x < width ; x++) {
                if ((x & 7) == 0) {
                    b = lbuff[x >> 3];
                }
                if ((b & srcMask) == 0) {
                    w |= mask;
                }
                srcMask = srcMask >> 1;
                if (0 == srcMask) {
                    srcMask = 0x80;
                }
                mask >>= 1;
                if (mask == 0) {
                    *dp++ = w;
                    w = 0;
                    mask = MSB32;
                }
            }
            if (mask != MSB32) {
                *dp++ = w;
            }
        }
    } else if (trueBpp == 2) {
        // 2 bits-per-pixel, for Q-Class. Colour table has been built to suit
        for (y = 0 ; y < height ; y++) {
            lbuff = (uint8 *)oBmp.GetPixelAddress(0, y);
            for (x = 0 ; x < width ; x += 2) {
                byteoff = x >> 1;
                shift = 4 *(7 - (byteoff & 7));	// Bit count to shift left
                b = ~lbuff[byteoff];			// Get two pixels in a byte (input is 4bpp). Invert for printer
                b = ((b >> 2) & 0x0C) | (b & 0x3);	// Align the pixels and convert to 2 bpp
                *dp |= ((uint32)b) << shift;	// Write both pixels
                if ((x >= width-2) || ((byteoff & 7) == 7)) {
                    dp++;
                }
            }
        }
    } else {	// trueBpp ==  3 or 4
        // 4 bits-per-pixel, for Leopard and 1001. Colour table has been built to suit
        bppMask = (1 << trueBpp) - 1;			// Make a mask to suit the true bpp
        bppMask |= bppMask << 4;				// Form mask for two pixels
        for (y = 0 ; y < height ; y++) {
            lbuff = (uint8 *)oBmp.GetPixelAddress(0, y);
            for (x = 0 ; x < width ; x += 2) {
                byteoff = x >> 1;
                shift = 8 *(3 - (byteoff & 3));	// Bit count to shift left
                b = ~lbuff[byteoff];			// Get two pixels in a byte. Invert for printer
                b &= bppMask;					// Mask for number of bits per pixel
                *dp |= ((uint32)b) << shift;	// Write both pixels
                if ((x >= width-2) || ((byteoff & 3) == 3))
                    dp++;
            }
        }
    }

    return pBuff;
}

