#include <Mouse.h>
#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_hu_HU.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_pt_PT.h>
#include <Keyboard_sv_SE.h>


const int xAxisPin = A0;
const int yAxisPin = A1;

const int centerValue = 512;

void setup() {
  Serial.begin(115200);
  Mouse.begin();
  Keyboard.begin();
  Mouse.press(MOUSE_RIGHT);
  Mouse.release(MOUSE_RIGHT);
  while (!Serial) { ; }

  String response = "connect successfully";
  Serial.println(response);
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    Serial.println(line); // Kiírja a fogadott sort a soros monitorba
    executeCommand(line);
  }
}

void executeCommand(String command) {
  char buf[50];
  command.toCharArray(buf, 50);
  
  char* cmdType = strtok(buf, ",");
  
    if (strcmp(cmdType, "up") == 0) {
    int val = atoi(strtok(NULL, ","));
    int count = atoi(strtok(NULL, ","));

    for (int i = 0; i < count; i++) {
      int yValue = analogRead(yAxisPin);
      int moveY = map(yValue, 0, 4095, 0, val);
      Mouse.move(0, -moveY);
    }
    Serial.println("done"); 
  }else if (strcmp(cmdType, "down") == 0) {
    int val = atoi(strtok(NULL, ","));
    int count = atoi(strtok(NULL, ","));

    for (int i = 0; i < count; i++) {
      int yValue = analogRead(yAxisPin);

      int moveY = map(yValue, 0, 4095, 0, val);
      Mouse.move(0, moveY);
    }
    Serial.println("done"); 
  }else if (strcmp(cmdType, "right") == 0) {
    int val = atoi(strtok(NULL, ","));
    int count = atoi(strtok(NULL, ","));

    for (int i = 0; i < count; i++) {
      int xValue = analogRead(xAxisPin);
      int moveX = map(xValue, 0, 4095, val, 0);
      Mouse.move(moveX, 0);
    }
    Serial.println("done"); 
  }
  else if (strcmp(cmdType, "left") == 0) {
    int val = atoi(strtok(NULL, ","));
    int count = atoi(strtok(NULL, ","));

    for (int i = 0; i < count; i++) {
      int xValue = analogRead(xAxisPin);
      int moveX = map(xValue, 0, 4095, val, 0);
      Mouse.move(-moveX, 0);
    }
    Serial.println("done"); 
  }else if (strcmp(cmdType, "mouse") == 0) {
    char* button = strtok(NULL, ",");
    char* action = strtok(NULL, ",");
    int d = atoi(strtok(NULL, ","));
    if(strcmp(button, "right") == 0){
      if(strcmp(action, "press") == 0){
        Mouse.press(MOUSE_RIGHT);
        Serial.println("done"); 
      }else if(strcmp(action, "release") == 0){
        Mouse.release(MOUSE_RIGHT);
        Serial.println("done"); 
      }
    }else if(strcmp(button, "left") == 0){
      Mouse.press(MOUSE_LEFT);
      delay(d);
      Mouse.release(MOUSE_LEFT);
      delay(200);
      Serial.println("done"); 
    }
    else{
    }
  } else if (strcmp(cmdType, "move") == 0) {
    int d = atoi(strtok(NULL, ","));
    Keyboard.press('w');
    delay(d);
    Keyboard.release('w');
    Serial.println("done"); 
  }
}


