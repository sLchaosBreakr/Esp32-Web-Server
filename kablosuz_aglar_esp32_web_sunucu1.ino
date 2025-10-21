#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_WebServer";
const char* password = "12345678"; // minimum 8 karakter olmalı

WebServer server(80);

void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <style>
      body {
        font-family: Arial, sans-serif;
        background-color: #f5f5f5;
        text-align: center;
        margin: 0;
        padding: 0;
      }
      h1 {
        background: #007bff;
        color: white;
        padding: 20px;
        margin: 0;
      }
      h2 {
        color: #333;
        margin-top: 30px;
      }
      ul {
        list-style-type: none;
        padding: 0;
        margin: 30px auto;
        max-width: 300px;
        background: white;
        border-radius: 10px;
        box-shadow: 0 4px 10px rgba(0,0,0,0.2);
      }
      li {
        padding: 10px;
        border-bottom: 1px solid #ddd;
        font-size: 18px;
        color: #333;
      }
      li:last-child {
        border-bottom: none;
      }
      footer {
        margin-top: 30px;
        font-size: 14px;
        color: #666;
      }
    </style>
  </head>
  <body>
    <h1>ESP32 Web Sunucu</h1>
    <p>Sunucu aktif ve calısıyor.</p>
    <p>IP Adresi: )rawliteral";
  
  html += WiFi.softAPIP().toString();
  
  html += R"rawliteral(</p>
    <h2>Katilimci Listesi</h2>
    <ul>
  )rawliteral";

  String names[9] = {
    "Mehmet Torun",
    "Mustafa Selman Uguz",
    "Nurullah Basar",
    "Muhammet Emin Kapucu",
    "Amine Zehra Ilkay",
    "Ali Damlapinar",
    "Efe Yilmaz",
    "Hasan Ozer",
    "Yusuf Selim Ulu"
  };

  for (int i = 0; i < 9; i++) {
    html += "<li>" + names[i] + "</li>";
  }

  html += R"rawliteral(
    </ul>
    <footer>2025 ESP32 Web Sunucu Ornegi</footer>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Access Point modu başlatılıyor...");

  // ESP32 kendi WiFi ağını oluşturur
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP adresi: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.begin();

  Serial.println("HTTP sunucu başlatıldı.");
}

void loop() {
  server.handleClient();
}
