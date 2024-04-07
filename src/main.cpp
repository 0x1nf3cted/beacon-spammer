#include <WiFi.h>
#include "esp_wifi.h"

// Beacon Packet buffer
uint8_t packet[128] = {0x80, 0x00, 0x00, 0x00,
                      /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                      /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                      /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                      /*22*/  0xc0, 0x6c,
                      /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
                      /*32*/  0x64, 0x00,
                      /*34*/  0x01, 0x04,
                      /* SSID */
                      /*36*/  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                      0x01, 0x08, 0x82, 0x84,
                      0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01,
                      /*56*/  0x04};



const char *names[] ={
    "404 Network Unavailable",
    "Pretty Fly for a WiFi",
    "The Promised LAN",
    "Get Off My LAN!",
    "Abraham Linksys",
    "The LAN Before Time",
    "LAN Solo",
    "Wu Tang LAN",
    "Drop It Like It's Hotspot",
    "FBI Surveillance Van",
    "Hide Yo Kids, Hide Yo WiFi",
    "Virus-Infected WiFi",
    "CIA Surveillance",
    "This LAN Is My LAN",
    "The Password Is 1234",
    "No Free WiFi For You",
    "The Internet Is Lava",
    "The WiFi Next Door",
    "Hogwarts Great Hall WiFi",
    "404 Wi-Fi Unavailable",
    "The Dark Knight Rises",
    "Skynet Global Defense Network",
    "NSA Listening Post",
    "Area 51 Test Site",
    "Yell 'Penis' for Password",
    "Go Go Gadget Internet",
    "Don't Even Try It",
    "A Van Down By The River",
    "WeCanHearYouHavingSex",
    "I'm Watching You Now",
    "Get Your Own Damn WiFi",
    "Abandon Hope All Ye Who Connect",
    "Look Ma, No Wires!",
    "Keep It On The Download",
    "The Password Is Potato",
    "The Silence of the LANs",
    "Wi Believe I Can Fi",
    "All Your Bandwidth Belong to Us",
    "Winternet Is Coming",
    "TellMyWiFiLoveHer",
    "You're Not Safe",
    "Martin Router King",
    "Get Off My Lawn",
    "Password is Gullible",
    "Access Denied",
    "404 Error: WiFi Not Found",
    "LAN of Milk and Honey",
    "No Free Internet Here",
    "This is Not Free Either",
    "LAN of the Dead",
    "The Wireless-G Spot",
    "LANd of the Free",
    "Free Public WiFi",
    "The Password Is Guest",
    "Connect and Die",
    "Unprotected CeX",
    "John Wilkes Bluetooth",
    "WillUmarryMe?",
    "TellMyWiFiSaidHello",
    "I'm Under Your Bed",
    "Covet Not Thy Neighbor's WiFi",
    "Ye Olde Internet",
    "Unprotected CeX",
    "NotTheWiFiYoureLookingFor",
    "This LAN Is Your LAN",
    "You Shall Not Password",
    "LANdo Calrissian",
    "One Does Not Simply Connect",
    "The LAN Down Under",
    "Look Ma, No Wires!",
    "Virus Distribution Center",
    "Silence of the LAN",
    "Access Denied",
    "C:\\Virus.exe",
    "Trojan Horse",
    "Connect and Die",
    "NoFreeInternetHere",
    "Mom Use This One",
    "Man Cave",
    "404 Wi-Fi Unavailable",
    "Titanic Syncing",
    "Go Home Tourists",
    "My Neighbors Suck",
    "Please Connect for Identity Theft",
    "It Burns When IP",
    "Free Virus",
    "To use, bring boozeJohn Wilkes Bluetooth",
    "Bill Wi, the Science Fi",
    "Drop It Like It's Hotspot",
    "2 Girls 1 Router",
    "I Pronounce You Man and WiFi",
    "PorqueFi",
    "One Does Not Simply Connect to WiFi",
    "Pretty Fly for a WiFi",
    "TellMyWiFiLoveHer",
    "I'm Under Your Bed",
    "Password is Password",
    "The Password Is 1234",
    "Virus Distribution Center",
    "Connect and Die",
    "Abandon Hope All Ye Who Connect",
    "Silence of the LAN",
    "Get Off My LAN!",
    "NoFreeInternetHere",
    "You Shall Not Password"
};

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  for (int i = 0; i < 100; ++i) {
    WiFi.begin(names[i], "password"); 

    Serial.print("Created Wi-Fi access point: ");
    Serial.println(names[i]);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  for (int i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {

    esp_wifi_set_channel(random(1, 14), WIFI_SECOND_CHAN_NONE);

    // Randomize source adress MAC
    for (int j = 10; j <= 21; j++) {
      packet[j] = random(256);
    }

    // Set SSID to the current name from names list
    const char *ssid = names[i];
    int ssidLength = strlen(ssid);
    packet[36] = ssidLength >> 8; // High byte of SSID length
    packet[37] = ssidLength & 0xFF; // Low byte of SSID length
    for (int j = 0; j < ssidLength; j++) {
      packet[38 + j] = ssid[j];  
    }

     esp_wifi_80211_tx(WIFI_IF_STA, packet, 38 + ssidLength, false);

    delay(1);
  }
}
