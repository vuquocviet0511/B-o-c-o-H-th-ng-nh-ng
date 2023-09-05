#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

TaskHandle_t Task1;
TaskHandle_t Task2;
const int buzzer = 2;
const int led2 = 4;
const int btn1 = 12;
int state1=0;
int state2=0;
int value = digitalRead(14);
void IRAM_ATTR isr(){
  state1=0;
  digitalWrite(buzzer, state1);
  state2=0;
  digitalWrite(led2, state2);
  delay(10);
}
void setup() {
  Serial.begin(921600);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(led2, OUTPUT);
  attachInterrupt(btn1, isr, HIGH);
  lcd.init();
  lcd.backlight();
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(50); 
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(50); 
}
void loop() {
  value = digitalRead(14);
  
  delay(100);
}
void LCD(){
    // set cursor to first column, first row
  lcd.setCursor(3, 0);
  lcd.print("WARNING!!!");
  delay(200);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("WARNING!!!");
  delay(200);
  lcd.clear();
}
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
    if (value ==0){
      Serial.println("Khong Rung");
      state1=0;
      digitalWrite(buzzer, state1);
    //  delay(0.00001);
    } 
    else if (value == 1){
      Serial.println("Rung");
      for (int i=0;i<20;i++){
        state1=1;
        digitalWrite(buzzer,state1);
        
        delay(100);
        LCD();
        if(state1==0){
         return;
         return;
        }
      }
    }   
  }
}
 
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
   if (state1==1) {
   state2=~state2;
   delay(100);
   digitalWrite(led2, state2);
   }
   else if (state1==0){
state2=0;
    digitalWrite(led2, state2);
   }
  } 
}
