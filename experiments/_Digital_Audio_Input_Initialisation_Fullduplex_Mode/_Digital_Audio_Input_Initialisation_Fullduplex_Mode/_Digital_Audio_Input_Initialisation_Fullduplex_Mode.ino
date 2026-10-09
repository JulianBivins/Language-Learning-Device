#include "driver/i2s_std.h"
#include "driver/gpio.h"
// Global handles that are automatically initiated to Null (I think)
i2s_chan_handle_t tx_handle;
i2s_chan_handle_t rx_handle;

void i2s_setup(){
  /* Allocate a pair of I2S channel */
  i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
  /* Allocate for TX and RX channel at the same time, then they will work in full-duplex mode */
  i2s_new_channel(&chan_cfg, &tx_handle, &rx_handle);
  /* Set the configurations for both channels. BCLK/WS and frame timing must match in full-duplex mode. */
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
  i2s_channel_init_std_mode(tx_handle, &std_cfg);
  i2s_channel_init_std_mode(rx_handle, &std_cfg);
  // Before reading or writing data, we need to start the TX & RX channels first
    //i2s_channel_enable(tx_handle);
    //i2s_channel_enable(rx_handle); 
}

// ==========================================
// TODO: NEXT STEPS FOR CONVO MVP
// ==========================================
// 1. Audio Input: Implement i2s_channel_read() to capture mic data (IO4)
// 2. Push-to-Talk: Add logic for the PTT button (IO35) to trigger recording
// 3. Audio Output: Receive AI response and play it via i2s_channel_write() to amplifier (IO7)
// 4. Cloud Link: Send recorded audio to backend (Moonshine/LLM)