#pragma once // Only needs to be loaded once 


// ====== Arduino IDE Board Settings (Tools menu): ====== 
//   - USB CDC On Boot:   "Enabled"    (Required for USB-C)
//   - PSRAM:             "OPI PSRAM"  (R8 -> 8MB Octal PSRAM )
//   - Core Debug Level:  "Info"       
//   - Flash Mode:        "QIO 80MHz"  (Quad SPI Flash on N4)
//   - Flash Size:        "4MB (32Mb)" (4MB Flash on N4)
//   - Upload Mode:       "UART0 / Hardware CDC"
//   - USB Mode:          "Hardware CDC and JTAG"
// ======================================================

// --- Buttons ---
#define PIN_BTN_BOOT 0
#define PIN_BTN_PTT 1
#define PIN_BTN_VOL_DOWN 9
#define PIN_BTN_VOL_UP 11

// --- I2S ---
#define PIN_I2S_SCK 6
#define PIN_I2S_WS 5
#define PIN_I2S_MIC_SD  4
#define PIN_I2S_AMP_DIN 7
#define PIN_I2S_AMP_SD_MODE 47 // Needs to be high to turn the AMP on (I think)

// --- I2C ---
#define PIN_I2C_SDA 2
#define PIN_I2C_SCL 15

// --- LCD ---
#define PIN_LCD_DATA_D0 38
#define PIN_LCD_DATA_D1 10
#define PIN_LCD_DATA_D2 48
#define PIN_LCD_DATA_D3 3
#define PIN_LCD_DATA_D4 12
#define PIN_LCD_DATA_D5 13
#define PIN_LCD_DATA_D6 14
#define PIN_LCD_DATA_D7 21
#define PIN_LCD_CHP_SLCT_CSX 39
#define PIN_LCD_WRT_WRX 40
#define PIN_LCD_RST_RESX 41

// --- Audio Parameters ---
#define SAMPLE_RATE_HZ  16000
#define DEBOUNCE_MS     50
