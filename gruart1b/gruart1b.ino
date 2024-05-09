#include <WiFiMulti.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>

#define PIN    19      // Pin de sortida Leds
#define nleds 300      // Nombre de leds
#define trams   2      // de moment dues línies


#include "index.h"

 WiFiMulti wifiMulti;

// const char* ssid = "ADAMO-CE6A";
// const char* password = "L7YWGPRVXGQLAM";
// const char* ssid = "CursosTAV";
// const char* password = "F3ntiD3sfent";

WebServer server(80);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nleds, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t connectTimeoutMs = 5000;
int ledsr[nleds];
int ledsg[nleds];
int ledsb[nleds];

int red    = 50;
int green  = 50;
int blue   = 50;
int nivell = 50;

int slider1Value = 50;
int slider2Value = 50;
int slider3Value = 50;
int slider4Value = 50;

String mensajeDesdeSerial = "";

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleSlidersStatus() {
  String slidersStatus = String(slider1Value) + "," + String(slider2Value) + "," + String(slider3Value) + "," + String(slider4Value);
  server.send(200, "text/plain", slidersStatus);
}

void handleSlider() {
  if (server.hasArg("slider1")) {
    slider1Value = server.arg("slider1").toInt();
    Serial.println("Slider 1: " + String(slider1Value));
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
    }
   pixels.setBrightness(slider1Value); 
   pixels.show();
   nivell = slider1Value;
  }

  if (server.hasArg("slider2")) {
    slider2Value = server.arg("slider2").toInt();
    Serial.println("Slider 2: " + String(slider2Value));
    red = slider2Value;
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
    }
  pixels.show();
  }
  if (server.hasArg("slider3")) {
    slider3Value = server.arg("slider3").toInt();
    Serial.println("Slider 3: " + String(slider3Value));
    green = slider3Value;
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
    }
  pixels.show();
  }
  if (server.hasArg("slider4")) {
    slider4Value = server.arg("slider4").toInt();
    Serial.println("Slider 4: " + String(slider4Value));
    blue = slider4Value;
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
    }
  pixels.show();
  }
  server.send(200, "text/plain", "Datos recibidos correctamente");
}

void handleButton() {
  String mensaje = server.arg("mensaje");
  Serial.println(mensaje);
  mensajeDesdeSerial = mensaje;
  server.send(200, "text/plain", "Mensaje recibido correctamente");
  if (mensaje == "ON") {
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
    } 
    pixels.setBrightness(nivell); 
    pixels.show();

    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
    } 
    pixels.setBrightness(nivell); 
    pixels.show();
    
    Serial.println(nivell);
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);

  } else if (mensaje == "OFF") {
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
    }
   pixels.setBrightness(0); 
   pixels.show();
  }      

}

void setup() {
  Serial.begin(115200);

  // Inicia lista de díodes WS2812 
  pixels.begin();
  for ( int i = 0; i < nleds; i++){
    ledsr[i] = 0; ledsg[i] = 0; ledsb[i] = 0; 
    pixels.setPixelColor(i,pixels.Color(0,0,0));
  }
 
  delay(100);
  pixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  pixels.show();

  Serial.println("");
  Serial.println("");
  Serial.println("\nMulti WiFi");
  Serial.println("");

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);


  // Register multi WiFi networks
  wifiMulti.addAP("ADAMO-CE6A", "L7YWGPRVXGQLAM");
  wifiMulti.addAP("CursosTAV", "F3ntiD3sfent");
  wifiMulti.addAP("BASE42", "41xequemP3rsiana");

  // Maintain WiFi connection
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    Serial.print("WiFi connectada a ");
    Serial.print(WiFi.SSID());
    Serial.print(" amb IP = ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi not connected!");
  }

/*
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
*/
  Serial.println("Conectado a WiFi");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/button", HTTP_GET, handleButton);
  server.on("/slider", HTTP_GET, handleSlider);

  server.begin();

  Serial.println("Servidor HTTP iniciat");

  for ( int i = 0; i < nleds; i++){
    pixels.setPixelColor(i,pixels.Color(50,50,50));
  }

}


void loop() {
  server.handleClient();

  if (Serial.available() > 0) {
    mensajeDesdeSerial = Serial.readStringUntil('\n');
    server.send(200, "text/plain", "Mensaje recibido correctamente");
    handleRoot(); // Actualiza la página para mostrar el nuevo mensaje
  }
}
