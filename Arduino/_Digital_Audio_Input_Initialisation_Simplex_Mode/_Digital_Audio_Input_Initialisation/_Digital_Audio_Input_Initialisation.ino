
#include <driver/i2s_std.h>
#include <driver/gpio.h>

//Implice Pointer Declaration to reference and access the to be allocared transmit and receive channels */
i2s_chan_handle_t tx_handle;
i2s_chan_handle_t rx_handle;

//Setting the ESP32 as Master. We use I2S_NUM_AUTO to automatically assign the free I2S port */
i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO,
I2S_ROLE_MASTER);

// ------------
// Allocate a new TX channel and get the handle of the Channel.  Wrapped in ERR_Check to catch allocation Errors 
// ------------

//i2s_new_channel(pointer to channel config., pointer to channel var., Only needed for synchr. Full-Duplex setup  )*/
ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_handle, NULL));

//Setting up line config*/
i2s_std_config_t std_tx_cfg = {
  .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000), //16kHz as Industry standard for voice/speech applications*/
  .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO),
  .gpio_cfg = {
    .mclk = I2S_GPIO_UNUSED,
    .bclk = GPIO_NUM_6,
    .ws = GPIO_NUM_5,
    .dout = GPIO_NUM_7 ,
    .din = I2S_GPIO_UNUSED,
    .invert_flags = {
      .mclk_inv = false,
      .bclk_inv = false,
      .ws_inv = false,
    },
  },
};
// Initialize the channel with ERROR handling */
ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle, &std_tx_cfg));
ESP_ERROR_CHECK(i2s_channel_enable(tx_handle));


// ------------
// RX channel will be registered on another I2S, if no other available I2S unit found it will return ESP_ERR_NOT_FOUND
// ------------
ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, NULL, &rx_handle));
i2s_std_config_t std_rx_cfg = {
  .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
  .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO),
  .gpio_cfg = {
    .mclk = I2S_GPIO_UNUSED,
    .bclk = GPIO_NUM_6,
    .ws = GPIO_NUM_5,
    .dout = I2S_GPIO_UNUSED,
    .din = GPIO_NUM_4, // Mic uses SD (Serial Data) Designator*/
    .invert_flags = {
      .mclk_inv = false,
      .bclk_inv = false,
      .ws_inv = false,
    },
  },
};
// Initialize the channel with ERROR handling */
ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle, &std_rx_cfg));
ESP_ERROR_CHECK(i2s_channel_enable(rx_handle));



// ==========================================
// TODO: NEXT STEPS FOR CONVO MVP
// ==========================================
// 1. Audio Input: Implement i2s_channel_read() to capture mic data (IO4)
// 2. Push-to-Talk: Add logic for the PTT button (IO35) to trigger recording
// 3. Audio Output: Receive AI response and play it via i2s_channel_write() to amplifier (IO7)
// 4. Cloud Link: Send recorded audio to backend (Moonshine/LLM)