
#include <WiFi.h>

#define WIFI_NETWORK ""
#define WIFI_PASSWORD ""
#define WIFI_TIMEOUT_MS 20000
#define FAILED "Failed"
#define SUCCESS "Success"
 

String connectToWifi() {
    Serial.print("Connecting to WiFi")
    Serial.print(WIFI_NETWORK);
    WiFi.mode(WIFI_STA); 
    WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

    unsigned long startAttemptTime = millis(); 

    while(WiFi.status() != WL_CONNECTED && (millis() - startAttemptTime) < WIFI_TIMEOUT_MS){
        Serial.print("."); // Log
        delay(100); // Wait 0.1s
    }

   if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nWiFi connection failed!");
        return FAILED; 
    } else {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP()); // Fixed printing for IPAddress object
        return SUCCESS; 
    }
}

