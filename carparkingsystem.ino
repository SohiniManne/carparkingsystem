
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);   
Servo myservo;

const int IR1 = 2;
const int IR2 = 3;
const int TOTAL_SLOTS = 4;
int Slot = TOTAL_SLOTS;      
int flag1 = 0;
int flag2 = 0;

void setup() {
    Serial.begin(9600); 

    lcd.begin(); 
    lcd.backlight(); 
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);

    myservo.attach(4);
    myservo.write(100); 

    lcd.setCursor(0, 0);
    lcd.print("     ARDUINO    ");
    lcd.setCursor(0, 1);
    lcd.print(" PARKING SYSTEM ");
    delay(2000);
    lcd.clear();
}

void loop() {
    if (digitalRead(IR1) == LOW && flag1 == 0) {
        if (Slot > 0) { 
            flag1 = 1;
            if (flag2 == 0) { 
                myservo.write(0); 
                Slot--; 
            }
        } else {
            lcd.setCursor(0, 0);
            lcd.print("    SORRY :(    ");  
            lcd.setCursor(0, 1);
            lcd.print("  Parking Full  "); 
            delay(3000);
            lcd.clear();
        }
    }

    if (digitalRead(IR2) == LOW && flag2 == 0) {
        flag2 = 1;
        if (flag1 == 0) { 
            if (Slot < TOTAL_SLOTS) {  
                myservo.write(0); 
                Slot++;  
            }
        }
    }

    if (flag1 == 1 && flag2 == 1) {
        delay(1000);
        myservo.write(100);
        flag1 = 0; 
        flag2 = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print("    WELCOME!    ");
    lcd.setCursor(0, 1);
    lcd.print("Slot Left: ");
    lcd.print(Slot);
    lcd.print(" "); // Clears any previous extra digits
}

