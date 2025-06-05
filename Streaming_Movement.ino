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
#include <ESP32Servo.h>

Servo servo1, servo2, servo3, servo4;
Servo servo5, servo6, servo7, servo8;
int pos = 0;

#define SERVO1_0 90
#define SERVO2_0 70
#define SERVO3_0 90
#define SERVO4_0 90
#define SERVO5_0 110
#define SERVO6_0 130
#define SERVO7_0 90
#define SERVO8_0 0

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
const char* ssid = "Lab-Modul";
const char* password = "RrH632Jc";

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

    camera_fb_t* foto = esp_camera_fb_get(); // Capture frame
    if (!foto) {
      return;
    }

    client.write(foto->buf, foto->len);
    client.println();
    client.stop();

    esp_camera_fb_return(foto); // frees memory
}
int direction;
int old_direction;

void Command(){
  String comand = server.arg("comand");
  Serial.println(comand);
  direction=comand.toInt();
}

class Spider {
  public:
    int stpt1, stpt2, stpt3, stpt4;
    int stpt5, stpt6, stpt7, stpt8;

    Spider() {
      zero();
    }

    void zero() {
      stpt1 = SERVO1_0;
      stpt2 = SERVO2_0;
      stpt3 = SERVO3_0;
      stpt4 = SERVO4_0;
      stpt5 = SERVO5_0;
      stpt6 = SERVO6_0;
      stpt7 = SERVO7_0;
      stpt8= SERVO8_0;
      pos1 = stpt1;
      pos2 = stpt2;
      pos3 = stpt3;
      pos4 = stpt4;
      pos5 = stpt5;
      pos6 = stpt6;
      pos7 = stpt7;
      pos8 = stpt8;
      tick();
      delay(1000);
    }

    void tick() {
      if (pos1<stpt1) pos1++;
      else if (pos1>stpt1) pos1--;
      if (pos2<stpt2) pos2++;
      else if (pos2>stpt2) pos2--;
      if (pos3<stpt3) pos3++;
      else if (pos3>stpt3) pos3--;
      if (pos4<stpt4) pos4++;
      else if (pos4>stpt4) pos4--;
      if (pos5<stpt5) pos5++;
      else if (pos5>stpt5) pos5--;
      if (pos6<stpt6) pos6++;
      else if (pos6>stpt6) pos6--;
      if (pos7<stpt7) pos7++;
      else if (pos7>stpt7) pos7--;
      if (pos8<stpt8) pos8++;
      else if (pos8>stpt8) pos8--;

      servo1.write(pos1);
      servo2.write(pos2);
      servo3.write(pos3);
      servo4.write(pos4);
      servo5.write(pos5);
      servo6.write(pos6);
      servo7.write(pos7);
      servo8.write(pos8);

      delay(10);
    }

    bool done() {
      return pos1==stpt1 && pos2==stpt2 && pos3==stpt3 && pos4==stpt4 && pos5==stpt5 && pos6==stpt6 && pos7==stpt7 && pos8==stpt8;
    }

  private:
    int pos1, pos2, pos3, pos4;
    int pos5, pos6, pos7, pos8;

};



Spider spidy;

//estats
int forward_state = 0;
int backward_state = 0;
int left_state = 0;
int right_state = 0;

// move_forward
void move_forward(void) {
  switch(forward_state) {
    case 0: forward_state = 1; break;
    case 1:
      spidy.stpt2 = 0;
      spidy.stpt4 = 180;
      if(spidy.done()){ forward_state = 2;}
      else{ return;}
      break;
    case 2:
      spidy.stpt2 = 90;
      spidy.stpt4 = 90;
      if(spidy.done()){ forward_state = 3;}
      else{ return;}
      break;
    case 3:
      spidy.stpt6 = 50;
      spidy.stpt8 = 150;
      if(spidy.done()){ forward_state = 4;
      }else{ return;}
      break;
    case 4:
      spidy.stpt6 = 130;
      spidy.stpt8 = 90;
      if(spidy.done()){ forward_state = 1;
      }else{ return;}
      break;
  }
}

// move_back
void move_back(void) {
  switch(backward_state) {
    case 0: backward_state = 1; break;
    case 1:
      spidy.stpt6 = 50;
      spidy.stpt8 = 150;
      if(spidy.done()){ backward_state = 2;
      }else{ return;}
      break;
    case 2:
      spidy.stpt6 = 130;
      spidy.stpt8 = 90;
      if(spidy.done()){ backward_state = 3;
      }else{ return;}
      break;
    case 3:
      spidy.stpt2 = 0;
      spidy.stpt4 = 180;
      if(spidy.done()){ backward_state = 4;
      }else{ return;}
      break;
    case 4:
      spidy.stpt2 = 90;
      spidy.stpt4 = 90;
      if(spidy.done()) {backward_state = 1;
      }else{ return;}
      break;

  }
}

// move_left
void move_left(void) {
  switch(left_state) {
    case 0: left_state = 1; break;
    case 1:
      spidy.stpt2 = 0;
      spidy.stpt6 = 130;
      if(spidy.done()) {left_state = 2;}
      else {return;}
      break;
    case 2:
      spidy.stpt2 = 90;
      spidy.stpt6 = 50;
      if(spidy.done()) {left_state = 3;}
      else {return;}
      break;
    case 3:
      spidy.stpt4 = 180;
      spidy.stpt8 = 90;
      if(spidy.done()) {left_state = 4;}
      else {return;}
      break;
    case 4:
      spidy.stpt4 = 90;
      spidy.stpt8 = 90;
      if(spidy.done()) {left_state = 1;}
      else {return;}
      break;
  }
}

// move_right
void move_right(void) {
  switch(right_state) {
    case 0: 
      right_state = 1; 
      break;
    case 1:
      spidy.stpt4 = 180;
      spidy.stpt8 = 90;
      if(spidy.done()) {right_state = 2;}
      else {return;}
      break;
    case 2:
      spidy.stpt4 = 90;
      spidy.stpt8 = 90;
      if(spidy.done()) {right_state = 3;}
      else {return;}
      break;
    case 3:
      spidy.stpt2 = 0;
      spidy.stpt6 = 130;
      if(spidy.done()) {right_state = 4;}
      else {return;}
      break;
    case 4:
      spidy.stpt2 = 90;
      spidy.stpt6 = 50;
      if(spidy.done()) {right_state = 1;}
      else {return;}
      break;
  }
}
void parada(void){
  spidy.stpt1 = SERVO1_0;
  spidy.stpt2 = SERVO2_0;
  spidy.stpt3 = SERVO3_0;
  spidy.stpt4 = SERVO4_0;
  spidy.stpt5 = SERVO5_0;
  spidy.stpt6 = SERVO6_0;
  spidy.stpt7 = SERVO7_0;
  spidy.stpt8= SERVO8_0;
}

void setup() {

  Serial.begin(115200);

  servo2.setPeriodHertz(50); servo2.attach(13);
 // servo3.setPeriodHertz(50); servo3.attach(4);
  servo4.setPeriodHertz(50); servo4.attach(15);
  //servo5.setPeriodHertz(50); servo5.attach(2);
  servo6.setPeriodHertz(50); servo6.attach(16);
  //servo7.setPeriodHertz(50); servo7.attach(0);
  servo8.setPeriodHertz(50); servo8.attach(14);

  spidy = Spider();

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

  //Start the Web server
  server.begin();
}

void loop_movement() { //switch
  if(old_direction != direction) {
    // reset all states  
    forward_state = 0;
    backward_state = 0;
    left_state = 0;
    right_state = 0;
  }
  old_direction = direction;
  Serial.println(direction);
  switch(direction){
    case 1:
      move_forward();
      break;
    case 2:
      move_back();
      break;
    case 3:
      move_right();
      break;
    case 4:
      move_left();
      break;
    case 5:
      parada();
      break;
   
  }
  
}

void loop() {
  server.handleClient();
  spidy.tick();
  loop_movement();
}
