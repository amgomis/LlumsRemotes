/*
*  Connexió automàtica a diverses WiFi per diversos locals
*  Implementat per una IP fixa a cada local
*  Antonimg, amgomis@gmail.com
*  17/05/2024
*/
// Comencem amb la definició de les característiques de cada WiFi
const char* ssid1 = "CASA";
const char* password1 = "xxxx";
const char* ip1 = "192.168.1.15";
const char* gw1 = "192.168.1.1";
const char* msk1 = "255.255.255.0";
const char* dns1_1 = "8.8.8.8";
const char* dns2_1 = "8.8.4.4";

const char* ssid2 = "CursosTAV";
const char* password2 = "xxxx";
const char* ip2 = "192.168.107.245";
const char* gw2 = "192.168.107.1";
const char* msk2 = "255.255.255.0";
const char* dns1_2 = "8.8.8.8";
const char* dns2_2 = "8.8.4.4";

const char* ssid3 = "AJUNTAMENT";
const char* password3 = "xxxx";
const char* ip3 = "192.168.1.245";
const char* gw3 = "192.168.1.1";
const char* msk3 = "255.255.255.0";
const char* dns1_3 = "8.8.8.8";
const char* dns2_3 = "8.8.4.4";

const char* ssid4 = "BASE42";
const char* password4 = "41xequemP3rsiana";
const char* ip4 = "192.168.107.15";
const char* gw4 = "192.168.107.1";
const char* msk4 = "255.255.255.0";
const char* dns1_4 = "8.8.8.8";
const char* dns2_4 = "8.8.4.4";

// Algunes funcions necessiten aquest tipus de variable, p.e. WiFi.config()
IPAddress l_ip;
IPAddress l_gw;
IPAddress l_msk;
IPAddress l_dns1;
IPAddress l_dns2;

// Estructura de les dades necessaries
struct WifiConfig {
  String ssid;
  String password;
  String ip;
  String gw;
  String msk;
  String dns1;
  String dns2;
};

//  Omplim el vector amb les dades 
WifiConfig wifiConfigs[] = {
  {ssid1, password1, ip1, gw1, msk1, dns1_1, dns2_1},
  {ssid2, password2, ip2, gw2, msk2, dns1_2, dns2_2},
  {ssid3, password3, ip3, gw3, msk3, dns1_3, dns2_3},
  {ssid4, password4, ip4, gw4, msk4, dns1_4, dns2_4},
};

// Quantitat de elements definits
const int numConfigs = sizeof(wifiConfigs) / sizeof(wifiConfigs[0]);

void wifiSetup() {
    // Posa el mode de funcionament i forsa la desconnexió si és que estava connectat.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    int n = WiFi.scanNetworks();
    int trobatIndex = -1;
    String trobatSSID = "";

    for (int i = 0; i < n; i++) {
      String ssid = WiFi.SSID(i);
      Serial.println("Trobada xarxa: " + ssid);
      for (int j = 0; j < numConfigs; j++) {
        if (ssid == wifiConfigs[j].ssid) {
          trobatIndex = j;
          trobatSSID = ssid;
          break;
        }
      }
      if (trobatIndex != -1) {
        break;
      }
    }
    
    if (trobatIndex != -1) {
      Serial.println("s'ha trobat SSID : " + trobatSSID);
      Serial.println("Index trobat     : " + String(trobatIndex));
    } else {
      Serial.println("No hi ha coincidències... ");
    }

    l_ip.fromString(wifiConfigs[trobatIndex].ip);
    l_gw.fromString(wifiConfigs[trobatIndex].gw);
    l_msk.fromString(wifiConfigs[trobatIndex].msk);
    l_dns1.fromString(wifiConfigs[trobatIndex].dns1);
    l_dns2.fromString(wifiConfigs[trobatIndex].dns2);

    if (!WiFi.config(l_ip, l_gw, l_msk, l_dns1, l_dns2)) {
      Serial.println("Error de connexió...");
    }

    WiFi.begin(wifiConfigs[trobatIndex].ssid, wifiConfigs[trobatIndex].password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connectant...");
    }
    Serial.println("Connectat: " + wifiConfigs[trobatIndex].ssid + ", IP:  " + WiFi.localIP().toString());

}  // wifiSetup
