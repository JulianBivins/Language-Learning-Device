#pragma once // Only needs to be loaded once 


// Initialising the Driver in Full Duplex Mode 
bool audio_init(void);

// Open and Closes RX Channel for the Mic
bool audio_rx_start(void);
bool audio_rx_stop(void);
