#include "driver/i2s_std.h"
#include "driver/gpio.h"

// Defining state variables 
#define HIGH 1
#define LOW 0
#define DEBOUNCE_TIME 50 // in milliseconds. Rough estimate of debounce Time
#define NUM_SAMPLES 256 // Number of audio samples per turn 

int32_t audio_32[NUM_SAMPLES]; // Assuming I2S slot will be configured for 32-Bit

int lastSteadyState = HIGH; // previous stat of the input pin 
int currentPttState; // the current reading from the input pin
int lastFlickerableState = HIGH; 
unsigned long lastDebounceTime = 0; // This captures the last time the output pin was toggled
size_t bytes_read = 0; 


void activate_mic(void){
  (i2s_setup();
  pinMode_setup();
  // Start of the Loop
  currentPttState = digitalRead(PTT_BTN);
  // Checking to see if the button has JUST been pressed and we waited long enough to ignore noise
  if (currentPttState != lastFlickerableState){
    // Resetting the debounce timer; 
    lastDebounceTime = millis();
    //Saving the last flickerable state 
    lastFlickerableState = currentPttState; 
  }

  if ((millis()-lastDebounceTime) > DEBOUNCE_TIME){
    //if entered = the reading is at has been stable longer than the debounce delay. Meaning we can interpret this as the actual current state

    // if Button is pressed, enter RUNNING state (See Finite-State-Machine)
    if(lastSteadyState == HIGH && currentPttState == LOW){
      // print that Push-To-Talk is activated 
      i2s_channel_enable(rx_handle); 
      if(currentPttState == LOW){
        // Explaining the parameters. Adjusting the Parameters either overworks the CPU or underworks it leading to delay (Latencys) in the Responses
          // (1) handle, (2) zielpuffer, (3) buffersize, (4) zeiger auf gelesene bytes, (5) timeout
            // (3) According to Avanshee: dma buffer size = dma_frame_num * slot_num * data_bit_width(32)/8 = NUM_SAMPLES (256) *  mono (1) * sizeof(int32_t) (4) = sizeof(audio_32) 
            // 
        esp_err_t ret = i2s_channel_read(rx_handle, audio_32, sizeof(audio_32), &bytes_read, portMAX_DELAY) 
            if (ret == ESP_OK && bytes_read > 0) {
                sendAudioToMoonshine(audio_32, bytes_read);
            }
      }
      
    }
    // if Buttons state goes from pressed to unpress
    else if (lastSteadyState == LOW && currentPttState == HIGH){
      // print that Push-To-Talk is deactivated 
      i2s_channel_disable(rx_handle); // Enter READY

      // Tell Moonshine we are finished and he should start transcribing
      finishedAudioForMoonshine();

    }
    // Updating last state
    lastSteadyState = currentState; 
  // END of the loop. There needs to be some kind of loop 
  }
}



