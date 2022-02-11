#if !defined(__MODEL_TYPE_H__)
    #define __MODEL_TYPE_H__

// 0x01~0x7F: MH1 Series
//
// MH1-XXXD (VIA module)
#define SERIES_MH1S30D      0x01
// MP1-XXXD (VIA module)
#define SERIES_MP1S30D      0x02

// MH1-XXXE
#define SERIES_MH1C50E      0x03
#define SERIES_MH1C70E      0x04
#define SERIES_MH1A12E      0x05

// MH1-XXXD
#define SERIES_MH1C50D      0x06
#define SERIES_MH1C70D      0x07
#define SERIES_MH1A12D      0x08

// MH1-XXXN
#define SERIES_MH1C50N      0x09
#define SERIES_MH1C70N      0x0A
#define SERIES_MH1A12N      0x0B

// 0x80~0xEF: MP1 Series
//
// MP1-XXXD-YY
#define SERIES_MP1C50D_10   0x80    // 10"
#define SERIES_MP1C70D_10   0x81
#define SERIES_MP1A10D_10   0x82
#define SERIES_MP1C50D_12   0x83    // 12"
#define SERIES_MP1C70D_12   0x84
#define SERIES_MP1A12D_12   0x85
#define SERIES_MP1C50D_15   0x86    // 15"
#define SERIES_MP1C70D_15   0x87
#define SERIES_MP1A12D_15   0x88

// MP1-XXXN-YY
#define SERIES_MP1C50N_10   0x90    // 10"
#define SERIES_MP1C70N_10   0x91
#define SERIES_MP1A10N_10   0x92

// PM1-XXXN-YY
#define SERIES_PM1A10N_08   0xC0

// PCIe-L231-B1
#define SERIES_PCIEL231B1   0xD0
////////////////////////////////////////////////////////////////////////////////////////////////////
//      Model type          API value   DeviceId register value
// MH1-XXXD
#define DEVID_MH1S30D       0x0210      // 0x4210/0x4211

// MH1-XXXN
#define DEVID_MH1C50N       0x0220      // 0x2200
#define DEVID_MH1C70N       0x0221      // 0x2210
#define DEVID_MH1A12N       0x0222      // 0x2220

// MH1-XXXD
#define DEVID_MH1C50D       0x0223      // 0x2230
#define DEVID_MH1C70D       0x0224      // 0x2240
#define DEVID_MH1A12D       0x0225      // 0x2250

// MH1-XXXE
#define DEVID_MH1C50E       0x0226      // 0x2260
#define DEVID_MH1C70E       0x0227      // 0x2270
#define DEVID_MH1A12E       0x0228      // 0x2280

// MP1-XXXD-YY
#define DEVID_MP1A10D_10    0x0130      // 0x1300
//#define DEVID_MP1C50D_12    0x0FFF      // 0x0000
//#define DEVID_MP1C70D_12    0x0FFF      // 0x0000
//#define DEVID_MP1A12D_12    0x0FFF      // 0x0000
#define DEVID_MP1C50D_15    0x0120      // 0x1200
#define DEVID_MP1C70D_15    0x0121      // 0x1210
#define DEVID_MP1A12D_15    0x0122      // 0x1220

// MP1-XXXG-YY
//#define DEVID_MP1A10G_10    0x0131      // 0x1310

// MP1-XXXN-YY
#define DEVID_MP1A10N_10    0x0131      // 0x1310

// PM1-XXXN-YY
#define DEVID_PM1A10N_08    0x0320      // 0x3200

// PCIe-L231-B1
#define DEVID_PCIEL231B1    0x1420      // 0x0420

#endif