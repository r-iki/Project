#include <WiFi.h>  // Gunakan <ESP8266WiFi.h> jika pakai ESP8266
#include <ArduinoWebsockets.h>

const char* ssid = "Wisma Sekawan 4";  
const char* password = "26262604";
const char* websocket_server = "wss://madu.software/ws/sensor/";  

using namespace websockets;
WebsocketsClient client;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 10000;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected!");

    if(client.connect(websocket_server)) {
        Serial.println("Connected to WebSocket Server!");
    } else {
        Serial.println("WebSocket Connection Failed!");
    }
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi disconnected, reconnecting...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
    }

    if (!client.available()) {
        Serial.println("WebSocket disconnected, reconnecting...");
        client.connect(websocket_server);
    }
    if (!client.available()) {
        Serial.println("WebSocket disconnected, reconnecting...");
        if(client.connect(websocket_server)) {
            client.connect(websocket_server);
            Serial.println("Reconnected to WebSocket!");
        } else {
            Serial.println("WebSocket Reconnection Failed!");
        }
    }

    if (millis() - lastSendTime >= sendInterval) {
        lastSendTime = millis();

        String message = "{";
        message += "\"name\": \"ESP32 Sensor\",";
        message += "\"uv_410\": " + String(random(100, 500)) + ",";
        message += "\"uv_435\": " + String(random(100, 500)) + ",";
        message += "\"uv_460\": " + String(random(100, 500)) + ",";
        message += "\"uv_485\": " + String(random(100, 500)) + ",";
        message += "\"uv_510\": " + String(random(100, 500)) + ",";
        message += "\"uv_535\": " + String(random(100, 500)) + ",";
        message += "\"vis_560\": " + String(random(100, 500)) + ",";
        message += "\"vis_585\": " + String(random(100, 500)) + ",";
        message += "\"vis_645\": " + String(random(100, 500)) + ",";
        message += "\"vis_705\": " + String(random(100, 500)) + ",";
        message += "\"vis_900\": " + String(random(100, 500)) + ",";
        message += "\"vis_940\": " + String(random(100, 500)) + ",";
        message += "\"nir_610\": " + String(random(100, 500)) + ",";
        message += "\"nir_680\": " + String(random(100, 500)) + ",";
        message += "\"nir_730\": " + String(random(100, 500)) + ",";
        message += "\"nir_760\": " + String(random(100, 500)) + ",";
        message += "\"nir_810\": " + String(random(100, 500)) + ",";
        message += "\"nir_860\": " + String(random(100, 500));
        message += "}";

        client.send(message);
        Serial.println("Data sent: " + message);
    }
}
