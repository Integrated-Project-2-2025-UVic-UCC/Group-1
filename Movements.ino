
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

//states
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
void stop(void){
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

  // Configure PWM frequency and pins
  servo1.setPeriodHertz(50); servo1.attach(12);
  servo2.setPeriodHertz(50); servo2.attach(13);
  servo3.setPeriodHertz(50); servo3.attach(4);
  servo4.setPeriodHertz(50); servo4.attach(15);
  servo5.setPeriodHertz(50); servo5.attach(2);
  servo6.setPeriodHertz(50); servo6.attach(16);
  servo7.setPeriodHertz(50); servo7.attach(0);
  servo8.setPeriodHertz(50); servo8.attach(14);

  spidy = Spider();
}

int direction;
int old_direction;

void loop_movement() { //switch
  if(old_direction != direction) {
    // reset all states  
    forward_state = 0;
    backward_state = 0;
    left_state = 0;
    right_state = 0;
  }
  old_direction = direction;
  switch(direction){
    case 0:
      move_forward();
      break;
    case 1:
      move_back();
      break;
    case 2:
      move_right();
      break;
    case 3:
      move_left();
      break;
    case 4:
      stop();
      break;
   
  }
  spidy.tick();

}

void loop() {
  spidy.tick();
  loop_movement();
}
