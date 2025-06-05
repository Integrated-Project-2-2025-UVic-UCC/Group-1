#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// ESP32-CAM AI-Thinker Pins
#define PWDN_GPIO_NUM  32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  0
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27

#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    21
#define Y4_GPIO_NUM    19
#define Y3_GPIO_NUM    18
#define Y2_GPIO_NUM    5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22

//Function that starts the camera
void StartCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 20;
  config.fb_count = 1;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Error when starting the camera");
  }
}

//Credencials de la red wifi a la que ens conectem
const char* ssid = "iPhone de Oscar";
const char* password = "oscar123";

//Select the port to which our web will listen (80 for web servers)
WebServer server(80);

//Web page function
void RouteHTML(){
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>ESP32-CAM</title>
    </head>
    <body>
      <h1>Streaming ESP32-CAM</h1>
      <button onclick="grab()">Start Streaming</button>
      <br><br>
      <img id="stream" src="" style="width:50%;">
      <br><br>
      <button onclick="SendID(1)">Forward</button>
      <button onclick="SendID(2)">Back</button>
      <button onclick="SendID(3)">Right</button>
      <button onclick="SendID(4)">Left</button>
      <button onclick="SendID(5)">Stop</button>
      <script>
        function grab() {
          document.getElementById("stream").src = "/stream?" + new Date().getTime();
          document.getElementById("stream").onload = function(){setTimeout(grab,30)};
        }
        function SendID(comand){
          fetch(`Command?comand=${comand}`)
            .then(response => {return response.text();})
            }
      </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

//Function to send frames
void controlStream(){
    WiFiClient client = server.client();

    camera_fb_t* foto = esp_camera_fb_get(); // Captura frame
    if (!foto) {
      return;
    }

    client.write(foto->buf, foto->len);
    client.println();
    client.stop();

    esp_camera_fb_return(foto); // Llibera la memoria
}

void Command(){
  String comand = server.arg("comand");
  Serial.println(comand);
}

void setup() {
  Serial.begin(115200);

  //Connect the ESP32 to the Wifi network
  WiFi.begin(ssid, password);

  //We give it time to initialize the Wifi connection
  Serial.println();
  Serial.println("Connecting to WiFi...");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print(".");
  }
  Serial.println("\nWiFi connected, IP: " + WiFi.localIP().toString()); 

  //Start the camera
  StartCamera();

  //Web page routes
    //Start web page
    server.on("/", HTTP_GET, RouteHTML);

    //Streaming Route
    server.on("/stream", HTTP_GET, controlStream);

    //Command Route
    server.on("/Command", HTTP_GET, Command);

;
  //Start the Web server
  server.begin();
}

void loop() {
  server.handleClient();
}
