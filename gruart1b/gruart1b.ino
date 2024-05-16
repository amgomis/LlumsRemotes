#define debug
#define multiwifi

#ifdef multiwifi
#include <WiFiMulti.h>
#endif
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>

#define PIN    19      // Pin de sortida Leds
#define RELE   18      // RELE de sortida
#define nleds 148      // Nombre de leds
#define trams   2      // de moment dues línies

#include "index.h"
#include "ssidpwd.h"

#ifdef multiwifi
 WiFiMulti wifiMulti;
#endif

WebServer server(80);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nleds, PIN, NEO_GRB + NEO_KHZ800);

// Macro per extreure els components R, G i B d'un color
#define RED(color)   (((color) >> 16) & 0xFF)
#define GREEN(color) (((color) >> 8) & 0xFF)
#define BLUE(color)  ((color) & 0xFF)

const uint32_t connectTimeoutMs = 5000;

uint32_t ncolor;

bool cslid[] = {false, false, false, false};
bool rgb   = false;

int red    = 50;  // Nivells inicials
int green  = 50;
int blue   = 50;
int nivell = 50;

int slider1Value = 50;  // Posicions inicials per defecte
int slider2Value = 50;
int slider3Value = 50;
int slider4Value = 50;

int dada   = 0;
int dada1  = 0;
int estat  = 0;
int estat1 = 0;
int obert  = 0;

int tseny;
int tarc;
int mleds;

String mensajeDesdeSerial = "";

// Funció per combinar els components R, G i B en un color uint32_t
uint32_t RGB_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
    // Assegura que els components estan dins del rang 0-255
    r = (r > 255) ? 255 : ((r < 0) ? 0 : r);
    g = (g > 255) ? 255 : ((g < 0) ? 0 : g);
    b = (b > 255) ? 255 : ((b < 0) ? 0 : b);

    // Combina els components en un color uint32_t
    uint32_t color = (r << 16) | (g << 8) | b;

    return color;
}

uint32_t colorRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

// Control Sliders
void handleSlider() {
//  dada  =  1;
//  estat = 20;
  
  if (server.hasArg("slider1")) {
    slider1Value = server.arg("slider1").toInt();
    nivell = slider1Value;
    cslid[0] = true;
  }
  if (server.hasArg("slider2")) {
    slider2Value = server.arg("slider2").toInt();
    red = slider2Value;
    cslid[1] = true;
  }
  if (server.hasArg("slider3")) {
    slider3Value = server.arg("slider3").toInt();
    green = slider3Value;
    cslid[2] = true;
  }
  if (server.hasArg("slider4")) {
    slider4Value = server.arg("slider4").toInt();
    blue = slider4Value;
    cslid[3] = true;
  }

  pixels.setBrightness(nivell); 
  ncolor = ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;

  if (rgb == true){
    for ( int i = 0; i < nleds; i++){
      pixels.setPixelColor(i,ncolor);
    }
//    encen_tira1_rgb();
//    encen_tira2_rgb();
    delay(10);
  }

#ifdef debug
    Serial.println("Intens.: " + String(slider1Value) + ",\t estat " + String(int(cslid[0])));
    Serial.println("Vermell: " + String(slider2Value) + ",\t estat " + String(int(cslid[1])));
    Serial.println("Verd   : " + String(slider3Value) + ",\t estat " + String(int(cslid[2])));
    Serial.println("Blau   : " + String(slider4Value) + ",\t estat " + String(int(cslid[3])));
#endif
  server.send(200, "text/plain", "Dades Rebudes correctament.");
}

// Manegament botons
void handleButton() {
  String mensaje = server.arg("mensaje");
#ifdef debug
  Serial.println(mensaje);
#endif
  mensajeDesdeSerial = mensaje;
  server.send(200, "text/plain", "Missatge rebut correctament");
  if (mensaje == "ON")           { estat =  1; dada = 1;}
  else if (mensaje == "OFF")     { estat =  2; dada = 1;}      
  else if (mensaje == "RL1_ON")  { estat =  3; dada = 1;}      
  else if (mensaje == "RL1_OFF") { estat =  4; dada = 1;}      
  else if (mensaje == "RGB")     { estat1 = 1; dada1 = 1;}      
  else if (mensaje == "SENY")    { estat1 = 2; dada1 = 1;}      
  else if (mensaje == "ARC")     { estat1 = 3; dada1 = 1;}      
  else if (mensaje == "MOBIL")   { estat1 = 4; dada1 = 1;}      
  else {estat = 0; dada = 0; dada1 = 0;}
}

// RGB
void RGB_out(){
//  Serial.print("rgb");
  if (obert) {
      for ( int i = 0; i < nleds; i++){
        pixels.setPixelColor(i,ncolor);
        }
      pixels.show();    
      delay(20);
  }
}

// Senyera
void SENY_out(){
  mleds = nleds;
  tseny = mleds / 9;
  // tira 1
  if (obert) {
    for ( int i = 0; i < tseny; i++){
      pixels.setPixelColor(i,colorRGB(255, 100, 0));
      }
      for ( int i = tseny; i < tseny * 2; i++){
        pixels.setPixelColor(i,colorRGB(255, 0, 0));
      }
      for ( int i = tseny * 2; i < tseny * 3; i++){
        pixels.setPixelColor(i,colorRGB(255, 100, 0));
      }
      for ( int i = tseny * 3; i < tseny * 4; i++){
        pixels.setPixelColor(i,colorRGB(255, 0, 0));
      }
      for ( int i = tseny * 4; i < tseny * 5; i++){
        pixels.setPixelColor(i,colorRGB(255, 100, 0));
      }
      for ( int i = tseny * 5; i < tseny * 6; i++){
        pixels.setPixelColor(i,colorRGB(255, 0, 0));
      }
      for ( int i = tseny * 6; i < tseny * 7; i++){
        pixels.setPixelColor(i,colorRGB(255, 100, 0));
      }
      for ( int i = tseny * 7; i < tseny * 8; i++){
        pixels.setPixelColor(i,colorRGB(255, 0, 0));
      }
      for ( int i = tseny * 8; i < mleds; i++){
        pixels.setPixelColor(i,colorRGB(255, 100, 0));
      }
    } else {
      for ( int i = 0; i < mleds; i++){
        pixels.setPixelColor(i,0);
      }
  }
    pixels.show();    
    delay(20);
}

void ARC_out(){
  mleds = nleds;
  tarc  = mleds / 6;
  if (obert) {
  // tira 1
    for ( int i = 0; i < tarc; i++){
      pixels.setPixelColor(i,colorRGB(255, 0, 0));
    }
    for ( int i = tarc * 1; i < tarc * 2; i++){
      pixels.setPixelColor(i,colorRGB(255, 60, 0));
    }
    for ( int i = tarc * 2; i < tarc * 3; i++){
      pixels.setPixelColor(i,colorRGB(255, 160, 0));
    }
    for ( int i = tarc * 3; i < tarc * 4; i++){
      pixels.setPixelColor(i,colorRGB(0, 255, 0));
    }
    for ( int i = tarc * 4; i < tarc * 5; i++){
      pixels.setPixelColor(i,colorRGB(0, 0, 255));
    }
    for ( int i = tarc * 5; i < mleds; i++){
      pixels.setPixelColor(i,colorRGB(128, 0, 128));
    }
  } else {
    for ( int i = 0; i < mleds; i++){
      pixels.setPixelColor(i,0);
    }
  }
  pixels.show();    
  delay(20);
}

void processa(){
  switch (estat) {
    case 0: {break;}
    // ON
    case 1: {  obert = true;
               dada  = 0;
               estat = 0;
      break;
      }
    // OFF
    case 2: {  obert = false;
               dada  = 0;
               estat = 0;
      break;
      }
    // RL1_ON
    case 3: {  digitalWrite(RELE, HIGH);
               dada  = 0;
               estat = 0;
      break;
      }
    // RL1_OFF
    case 4: {  digitalWrite(RELE, LOW);
               dada  = 0;
               estat = 0;
      break;
      }
  }
}

void rainbow() {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixels.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();
    delay(10);
  }
}

void setup() {
  Serial.begin(115200);
  // Inicia lista de díodes WS2812 
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);
  // Inicia pixels
  pixels.begin();
  // Tots apagats
  for ( int i = 0; i < nleds; i++){
    pixels.setPixelColor(i,colorRGB(0,0,0));
  }
  delay(100);
  pixels.setBrightness(nivell); // Brillantor inicial a 1/5 part (màxim = 255)
  pixels.show();  // Envia pixels
#ifdef multiwifi
  Serial.println("");
  Serial.println("");
  Serial.println("\nMulti WiFi");
  Serial.println("");
  // WiFi en mode estació
  WiFi.mode(WIFI_STA);
  // Register multi WiFi networks
  wifiMulti.addAP(ssid1, password1);
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3, password3);
  wifiMulti.addAP(ssid4, password4);
  // Connexió WiFi
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    Serial.print("WiFi connectada a ");
    Serial.print(WiFi.SSID());
    Serial.print(" amb IP = ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi no connectada!");
  }

#else
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectant a la WiFi...");
  }
  Serial.print("Connectat a la WiFi");
  Serial.print(" amb IP : ");
  Serial.println(WiFi.localIP());
#endif
  // rutines web
  server.on("/", HTTP_GET, handleRoot);
  server.on("/button", HTTP_GET, handleButton);
  server.on("/slider", HTTP_GET, handleSlider);
  server.begin();
  Serial.println("Servidor HTTP iniciat");
}

void loop() {
  server.handleClient();
  if (dada == 1){
    processa();
    dada = 0;    
  }
  if (obert) {
    if (estat1 == 1){
      RGB_out();
    } else 
    if (estat1 == 2){
      SENY_out();
    } else 
    if (estat1 == 3){
      ARC_out();
    } else 
    if (estat1 == 4){
      rainbow();
    } 
  } else {
  for ( int i = 0; i < nleds; i++){
    pixels.setPixelColor(i,0);
    }
  pixels.show();
  delay(10);
  }
}
