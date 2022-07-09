 #include "configuration.h"
 int sensor[5];
 /*read line folloe sensors*/
void read_sensor_values()
{
  sensor[0]=digitalRead(LFSensor_0);
  sensor[1]=digitalRead(LFSensor_1);
  sensor[2]=digitalRead(LFSensor_2);
  sensor[3]=digitalRead(LFSensor_3);
  sensor[4]=digitalRead(LFSensor_4);
}

void go_Advance(void)  //Forward
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Left(void)  //Turn left
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void go_Right(void)  //Turn right
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Back(void)  //Reverse
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}
/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void setup()
{
 pinMode(speedPinL,OUTPUT); //left motor PWM pin
 pinMode(speedPinR,OUTPUT); //rignt motor PWM  pin
 pinMode(dir1PinL,OUTPUT); //left motor direction pin1
 pinMode(dir2PinL,OUTPUT); //left motor direction pin2
 pinMode(dir1PinR,OUTPUT); //right motor direction Pin 1
 pinMode(dir2PinR,OUTPUT);  //right motor direction Pin 2

  /*line follow sensors */
 pinMode(LFSensor_0,INPUT);
 pinMode(LFSensor_1,INPUT);
 pinMode(LFSensor_2,INPUT);
 pinMode(LFSensor_3,INPUT);
 pinMode(LFSensor_4,INPUT); 
 Serial.begin(9600);
}

void auto_tarcking(){
  read_sensor_values();
  if(sensor[2]==HIGH){ //The middle sensor is on the black line
    if(sensor[1]==LOW && sensor[3]==LOW){ //Other sensors are in the white area
      go_Advance();  //straight
      set_Motorspeed(M_SPEED1,M_SPEED1);
    }
    else if(sensor[1]==HIGH && sensor[3]==LOW){ //The second sensor is also on the black line
       go_Left();  //Turn left
       set_Motorspeed(0,M_SPEED1);
    }
    else if(sensor[1]==LOW && sensor[3]==HIGH){  //The fourth sensor is also on the black line
      go_Right();  //Turn right
      set_Motorspeed(M_SPEED1,0);
    }
  }
  else if(sensor[2]==LOW){  //The middle sensor is in the white area
    if(sensor[1]==HIGH && sensor[3]==LOW){ //Turn left
      go_Left();  
      set_Motorspeed(0,M_SPEED1);
    }
    else if(sensor[1]==LOW && sensor[3]==HIGH){  //Turn right
       go_Right();
       set_Motorspeed(M_SPEED1,0);
    }
  }
  else {
     go_Back();
     set_Motorspeed(M_SPEED1,M_SPEED1);
  }
  if(sensor[1]==HIGH){  //The second sensor is on the black line
    if(sensor[0]==HIGH && sensor[2]==LOW){ //Accelerate left turn
      go_Left();
      set_Motorspeed(0,M_SPEED2);
    }
    else{  //Turn left
      go_Left();
      set_Motorspeed(0,M_SPEED1);
    }
  }
  if(sensor[3]==HIGH){  //The fourth sensor is on the black line
    if(sensor[2]==LOW && sensor[4]==HIGH){  //Accelerate right turn
      go_Right();
      set_Motorspeed(M_SPEED2,0);
    }
    else{  //Turn right
      go_Right();
      set_Motorspeed(M_SPEED1,0);
    }
  }
}
void loop(){
  auto_tarcking();
}

