#include "audio.h" 
#include "config.h"

#include "driver/i2s_std.h"
#include "driver/gpio.h"
// Global handles that are automatically initiated to Null (I think)
i2s_chan_handle_t tx_handle;
i2s_chan_handle_t rx_handle;

bool audio_init(void) {
// Allocate a pair of I2S channel 
  i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
// Allocate for TX and RX channel at the same time, then they will work in full-duplex mode
// Errorhandling to catch unsuccessfull initialisation
  esp_err_t ret = i2s_new_channel(&chan_cfg, &tx_handle, &rx_handle);
  if (ret != ESP_OK) {
    Serial.printf("--AUDIO-- ERROR with initialising i2s_new_channel: 0x%x\n", ret); // Check ESP-IDF ERROR Definitions
    return false;
  }


  // Set the configurations for both channels. BCLK/WS and frame timing must match in full-duplex mode. 
  i2s_std_config_t std_cfg = {
    .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
    .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO),
    .gpio_cfg = {
      .mclk = I2S_GPIO_UNUSED,
      .bclk = GPIO_NUM_6, // Shared Clock
      .ws = GPIO_NUM_5, // Shared Word Select
      .dout = GPIO_NUM_7, // To the Amplifier's DIN
      .din = GPIO_NUM_4, // From Microphone's SD
      .invert_flags = {
        .mclk_inv = false,
        .bclk_inv = false,
        .ws_inv = false,
      },
    },
  };
  // Initializing both channels with the shared configuration -> We are now in the READY State (See diagramm Finite-State-Machine)
  ret = i2s_channel_init_std_mode(tx_handle, &std_cfg);
  if (ret != ESP_OK) {
    Serial.printf("--AUDIO-- ERROR with initialising TX Channel: 0x%x\n", ret); 
    return false;
  }
  ret = i2s_channel_init_std_mode(rx_handle, &std_cfg);
  if (ret != ESP_OK) {
    Serial.printf("--AUDIO-- ERROR with initialising RX Channel: 0x%x\n", ret); 
    return false;
  }

  Serial.println("---AUDIO-- I2S Vollduplex initialisation is fully realised.");
  return true;
}


