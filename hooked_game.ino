#include <ButtonEvent.h>

const int START_BUTTON = 7;
const int PLAY_BUTTON = 8;

const int RESET_LED = 13;
const int READY_LED = 12;
const int GAME_LED_RED = 4;
const int GAME_LED_GREEN = 2;

// flashing
long previousMillis = 0;
long interval = 1000;
int ledState = LOW;  

int game_state = 0;

void setup() {

  ButtonEvent.addButton(START_BUTTON,       //button pin
                        onDown,   //onDown event function
                        onUp,     //onUp event function
                        onHold,   //onHold event function
                        1000,     //hold time in milliseconds
                        onDouble, //double event function
                        200);     //double time interval

  ButtonEvent.addButton(PLAY_BUTTON,       //button pin
                        onDown,   //onDown event function
                        onUp,     //onUp event function
                        onHold,   //onHold event function
                        1000,     //hold time in milliseconds
                        onDouble, //double event function
                        200);     //double time interval

  
  Serial.begin(9600);
  
  pinMode(RESET_LED, OUTPUT);
  pinMode(READY_LED, OUTPUT);
  pinMode(GAME_LED_RED, OUTPUT);
  pinMode(GAME_LED_GREEN, OUTPUT);
  
  randomSeed(analogRead(0));
}


void onDown(ButtonInformation* Sender) {
  
  if(Sender->pin == START_BUTTON) {
    if (game_state == 0) {
      game_state = 1;
    } 
  } else if (Sender->pin == PLAY_BUTTON) {
     if (game_state == 1) {
        game_state = 2;
     } 
  }
  
  printGameState();
}

void onUp(ButtonInformation* Sender) {}

void onHold(ButtonInformation* Sender) {}

void onDouble(ButtonInformation* Sender) {}


void printGameState() {
  Serial.print("Game State: ");
  Serial.print(game_state);
  Serial.print("\n");
}

void loop() {
      
  if (game_state == 0) {

    digitalWrite(READY_LED, LOW);
    
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) { 
      previousMillis = currentMillis;
     if (ledState == LOW){
         ledState = HIGH;
     } else {
         ledState = LOW;
     }
     digitalWrite(RESET_LED, ledState);
   }
           
  } else if (game_state == 1) {

    digitalWrite(RESET_LED, LOW);
    digitalWrite(READY_LED, HIGH);
    
  } else if (game_state == 2) {
    
    digitalWrite(RESET_LED, LOW);
    digitalWrite(READY_LED, LOW);

     
     for (float blink_delay = 1000; blink_delay > 2; blink_delay = blink_delay * 0.85) {
      digitalWrite(GAME_LED_RED, HIGH);
      digitalWrite(GAME_LED_GREEN, LOW);
      delay(blink_delay);
      digitalWrite(GAME_LED_RED, LOW);
      digitalWrite(GAME_LED_GREEN, HIGH);
      delay(blink_delay);
      digitalWrite(GAME_LED_RED, HIGH);
      digitalWrite(GAME_LED_GREEN, LOW);
    }      
    
    long randNumber = random(10);
    
    digitalWrite(GAME_LED_RED, LOW);
    digitalWrite(GAME_LED_GREEN, LOW);
    
    if(randNumber % 2 == 0) {
      digitalWrite(GAME_LED_RED, LOW);
      digitalWrite(GAME_LED_GREEN, HIGH);
    } else {
      digitalWrite(GAME_LED_RED, HIGH);
      digitalWrite(GAME_LED_GREEN, LOW);
    }

    delay(3000);    
    digitalWrite(GAME_LED_RED, LOW);
    digitalWrite(GAME_LED_GREEN, LOW);
    
    game_state = 0;
 
  }
  
  ButtonEvent.loop();
}
