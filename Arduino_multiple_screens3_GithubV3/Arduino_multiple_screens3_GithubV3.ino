/*  This menu by Kyle Campbell
    LCD-BLUE-12C libraries are here - https://arduino-info.wikispaces.com/LCD-Blue-I2C and here https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
    Menu structure also see Nicolas Jarpa here -  http://www.instructables.com/id/Arduino-LCD-16x2-Turn-Single-Screen-Into-Multiple-/
      


*/

// ========================================
// my screen info
#include <Wire.h>  // Comes with Arduino IDE
#include <Servo.h> //include servo library


// Get NEW LCD Libraies, see above comments 
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x3F for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
Servo myservo;  // create servo object to control a servo 

// =========================================
//Counters to change positions of pages and sub-menus

int page_counter=1 ;       //To move between pages

int subpage1_counter=0;   //To move submenu 1 
int subpage2_counter=0;   //To move submenu 2 
int subpage3_counter=0;   //To move submenu 3
int subpage4_counter=0;   //To move submenu 4 
int subpage5_counter=0;   //To move submenu 5 
int subpage6_counter=0;   //To move submenu 6
int subpage7_counter=0;   //To move submenu 7
int subpage8_counter=0;   //To move submenu 8

//-------Pins-----//
const int up = 3;          // Up/Yes button 
const int sel = 5;         // Select button
const int down = 4;        // Down/No button
const int led = 13;        // Led (pwm output)
const int potpin = A0;     // analog pin used to connect the SERVO potentiometer


//Variables for positions, pages and sub-menus

int sMin = 0;              // initial variables for servo mapping
int sMax = 180;            // initial variables for servo mapping
int readMin;
int readMax;

int val1;             // variable to read the value from the Manual SERVO mode analog pin 
int val2 = 90;             // Page 2 - variable to read the value Auto set-A 
int val3 = 45;             // Page 3 - variable to read the value Auto set-B 
int val4 = 0;              // Page 4 - SWEEP Variable
int val5 = 0;                // Page 5 - spare
int val6 = 0;                // Page 6 - spare
int val7 = 0;
int val8 = 0;


// int LCDValClear();         // used to clear any numbers on the servo readout position, is uses ("  ") method


//---------Storage states of buttons for debounce function-----//
boolean current_up = LOW;          
boolean last_up=LOW;            
boolean current_sel = LOW;
boolean last_sel = LOW;
boolean last_down = LOW;
boolean current_down = LOW;
//--------Led states-----------//
// boolean red_state = LOW;
// boolean green_state = LOW;
// boolean blue_state = LOW;
int led_lum =00;

// ====================================================================================       
// Voltage testers setup here...
    int VinA2, VinA3;       // Voltage tester connected to pins A2 and A3, A2 is the external power/battery input 5-15v and A3 is the voltage regulated 5v output to servo
    float VoutA2, VoutA3;   // float allows decimal point numbers
// ==================================



void setup() {
// =====================================================================================
  
    Serial.begin(9600);  // Used to type in characters
    Serial.print("hello screen");
    
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object  
    myservo.write(0);  // <------ put the servo at zero
// ==================================================================

// My screen writing of display lines here....

   lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight

// ------- Quick 2 blinks of backlight  -------------
  for(int i = 0; i< 2; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

  

//-------- Write characters on the display ------------------
  // NOTE: Cursor Position: Lines across 0-19 then Rows down 0-3. Characters start at 0,0 

  // Top line (0) to show the auto and manual servo angles
  lcd.setCursor(10,0);
  lcd.print("Angle:");      //  this will have text added before it from the switch menu selections
  // delay(1000);  
 
   // Second line (1) to Page show the auto and manual servo angles
  lcd.setCursor(0,1);       //Start at character  on line 1 page number goes here
  lcd.print("Page:");
  lcd.setCursor(9,1);       //Start at character  on line 9
  lcd.print("Active:");     // Yes or No will go here
  // delay(1000);
  
   // Third line (2) to show Voltage Inputs and Servo minimum angle (SMIN)
  lcd.setCursor(1,2);
  lcd.print("VIN:");    
  

   
  lcd.setCursor(11,2);
  lcd.print("SMIN:");  
   
   // Fourth line (3) to show Voltage Outs and Servo maximum angle (SMAX)
  lcd.setCursor(0,3);
  lcd.print("VOUT:");
  
  lcd.setCursor(11,3);
  lcd.print("SMAX:"); 




}
// =====================================================================================

   //---- De-bouncing function for all buttons----//
boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}



void loop() {

// ==========================
// Voltage tester code here...
 {
 float temp1,temp2;
      VinA2=analogRead(A2), VinA3=analogRead(A3);   // input pins from volts testers
     
      
      temp1=VinA2/4.092, temp2=VinA3/4.092;  // division maths to allow arduino to read higher voltages than 5-v
      VoutA2=(temp1/10),VoutA3=(temp2/10);   // 
      
 //     Serial.print("A2 Voltage input:");    // display for testing purposes
 //     Serial.println(VoutA2);
 //     Serial.print("A3 Voltage output:");
 //     Serial.println(VoutA3);

  //if (VoutA2<10){    
  lcd.setCursor(5,2);
  lcd.print(VoutA2);    // volts tester to servo   
  //lcd.setCursor(5,2);
  //lcd.print(" ");
  //}
  //else {
  //lcd.setCursor(5,2);
  //lcd.print(VoutA2);    // volts tester to servo  
  //}
      
  
  lcd.setCursor(5,3);   // volts tester from external power input/battery
  lcd.print(VoutA3);     
    delay(100);    
 }

// ==========================

// Now debounce buttons etc  

current_up = debounce(last_up, up);         //Debounce for Up button
current_sel = debounce(last_sel, sel);      //Debounce for Select  button
current_down = debounce(last_down, down);   //Debounce for Down button
// ====================================================================================================================================================
//----Page counter function to move pages----//

// ---Up and Down buttons are only enabled when "subpage_counter" is equal to "0" otherwise if "1" they are disabled and sub menus are activated
// ====================================================================================================================================================

         if(subpage1_counter==0 && subpage2_counter==0 && subpage3_counter==0 && subpage4_counter==0 && subpage5_counter==0 && subpage6_counter==0 && subpage7_counter==0 && subpage8_counter==0)
         {                 // up/down buttons enabled if subcounters are 0,Disabled if 1,2..etc to work on submenus
          
        //Page Up
            if (last_up== LOW && current_up == HIGH){ //Up button pressed
              
              if(page_counter <8){              //Page counter never higher than 3(total of pages)  NOW to 6
              page_counter= page_counter +1;   //Page up
              
              }
              else{
              page_counter= 1;                 //If higher than 3 (last page) stay on page 3(change to 1 if you want to rotate) NOW to 6
              }
          
        }
        
         
        last_up = current_up;                 //Save up button last state 
        
        //Page Down
            if (last_down== LOW && current_down == HIGH){//Down button pressed
              
              if(page_counter >1){              //Page counter never lower than 1 (total of pages)
              page_counter= page_counter -1;   //Page down
              
              }
              else{
              page_counter= 8;                 //If lower than 1(first page) stay on page 1(change to 8 if you want to rotate)
              }
          }
            
            last_down = current_down;         //Save down button last state
        }

// =========================================================================================================
//------- Switch function to write and show what you want---// 
// =========================================================================================================
  switch (page_counter) {// switch start and see "void SubMenuSel_()" for actual commands at bottom of page
    case 1:
    SubMenuSel_1();   //Manual Servo
    break;
// ==============================================================================
    case 2: 
    SubMenuSel_2();   //90-deg
    break;
// ==============================================================================
    case 3: 
    SubMenuSel_3();   //45-deg
    break;
// ==============================================================================                             
    case 4:
    SubMenuSel_4();   //Sweep
    break;
// ==============================================================================
    case 5:
    SubMenuSel_5();   // Spare
    break;
// ==============================================================================
    case 6:
    SubMenuSel_6();   // Spare
    break;
// ==============================================================================    
    case 7:
    SubMenuSel_7();   //SMin adjust
    break;
// ==============================================================================    
    case 8:
    SubMenuSel_8();   //SMax adjust
    break;
// ==============================================================================    
  
  }//switch end 
    
}// void-loop end








// ===============================
//  Functions here...
// ======================================================================
void SubMenuSel_1()
 {   //Design of page 1
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print("   ");  // clears previous text, 8 gaps
     lcd.setCursor(3,0);   
     lcd.print("Manual");  // this writes "manual" word, before "angle:"             
     
     lcd.setCursor(5,1);
     lcd.print(page_counter);  // this shows page number variable, in this instance page-1

     // ======================================================================================
     //Selector button   SubSelector  is 1 and locks page-menu item so it cannot change,  pressing select or toggles sub-sel betweem 0 & 1 so 0 releases page============
     // 
     //Sub counter 1 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage1_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage1_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage1_counter=0;
     }
     }
     last_sel=current_sel;   
    // =========================================================================================== 
    //Command item for subpage1_counter=1 
     if(subpage1_counter==1){  //main "if" start bracket

     lcd.setCursor(16,1); 
     lcd.print(subpage1_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              val1 = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
              val1 = map(val1, 0, 1023, sMin, sMax);     // scale it to use it with the servo (value between 1 and 180) 
              myservo.write(val1);                  // sets the servo position according to the scaled value    
              Serial.print("                 servo is at:");
              Serial.println(val1);             
              Serial.print("sMin value:");
              Serial.println(sMin);
              Serial.print("sMax value:");
              Serial.println(sMax);
              delay(500); 
              
              cursorPosition(val1);   // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).              
                                                       

                                                          
                 } //main "if" end bracket 
           
           else{ // else start bracket
           lcd.setCursor(16,1);
           lcd.print(subpage1_counter);  // this shows selector state variable, 0 which is OFF
           // now stop doing it        
           }  // else end bracket

    }//SubMenu void end bracket



//===========================================================================
//===========================================================================
void SubMenuSel_2()
     { //start void submenu2
     //Design of page 2
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print("     ");  // clears previous text, 5 gaps
     lcd.setCursor(5,0);   
     lcd.print("Auto");  // this writes "auto" word, before "angle:"             
     
     lcd.setCursor(5,1);
     lcd.print(page_counter);  // this shows page number variable, in this instance page-1
     
     //Selector button ======    SubSelector  is 2 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page=====
     //Sub counter 2 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage2_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage2_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage2_counter=0;
     }
     }
     last_sel=current_sel;   
    // ================================== 
    //Command item for subpage1_counter=1  
     if(subpage2_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage2_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              // val2 = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
              // val2 = map(val2, 0, 1023, 1, 180);     // scale it to use it with the servo (value between 1 and 180) 
              myservo.write(val2);                  // sets the servo position according to the scaled value    
              // Serial.println("Menu-1, Manual Servo Control - Enabled");
              Serial.print("Auto Position:");
              Serial.println(val2);
              delay(500); 

      // and write cursor position here...using cursorPosition() function to make layout consistant
              
              cursorPosition(val2);   // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).              
                                         
     }  
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage2_counter);  // this shows selector state variable, 0 which is OFF
     // now stop doing it    
     
     }

    }//end void sub menu2 end

//===========================================================================
//===========================================================================
void SubMenuSel_3()
     { //start void submenu3
     //Design of page 3
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print("     ");  // clears previous text, 5 gaps
     lcd.setCursor(5,0);   
     lcd.print("Auto");  // this writes "auto" word, before "angle:"             
     
     lcd.setCursor(5,1);
     lcd.print(page_counter);  // this shows page number variable, in this instance page-1
     
     //Selector button ======    SubSelector  is 3 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page============
     //Sub counter 3 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage3_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage3_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage3_counter=0;
     }
     }
     last_sel=current_sel;   
    // ==================
    //Command item for subpage6_counter=1  
     if(subpage3_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage3_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              //val3 = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
              //val3 = map(val3, 0, 1023, 1, 180);     // scale it to use it with the servo (value between 1 and 180) 
              myservo.write(val3);                  // sets the servo position according to the scaled value    
              // Serial.println("Menu-1, Manual Servo Control - Enabled");
              Serial.print("Auto Position:");
              Serial.println(val3);
              delay(500); 

              
              // and write cursor position here...using cursorPosition() function to make layout consistant
              cursorPosition(val3);   // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).   
                                      // This way  I can easily change number layout on the screen using the void cursorPosition  



                                      
     }  
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage3_counter);  // this shows selector state variable, 0 which is OFF
     // now stop doing it    
     
     }

    }//end void sub menu3 end

//========================================================================
//========================================================================
void SubMenuSel_4()     { //start void submenu4 SWEEP!!
     //Design of page 4
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print("     ");  // clears previous text, 5 gaps
     lcd.setCursor(4,0);   
     lcd.print("Sweep");  // this writes "Sweep" word, before "angle:"             
     
     lcd.setCursor(5,1);
     lcd.print(page_counter);  // this shows page number variable, in this instance page-1
     
     //Selector button ======    SubSelector  is 2 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page============
     //Sub counter 2 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage4_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage4_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage4_counter=0;
     }
     }
     last_sel=current_sel;   
    // ===================
    //Command item for subpage6_counter=1  
     if(subpage4_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage4_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              val4 = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
              val4 = map(val4, 0, 1023, 1, 180);     // scale it to use it with the servo (value between 1 and 180) 
              myservo.write(val4);                  // sets the servo position according to the scaled value    
              // Serial.println("Menu-1, Manual Servo Control - Enabled");
              Serial.print("Sweep:");
              Serial.println(val4);
              delay(500); 
              
              // and write cursor position here...using cursorPosition() function to make layout consistant
              cursorPosition(val4);   // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).   
                                      // This way  I can easily change number layout on the screen using the void cursorPosition  


// this Sweep "for loop" will not breakout and just locks up the buttons. Try a different approach

/*

maybe something like this here - REQUIRES MODIFYING
Notes - https://stackoverflow.com/questions/17391670/how-can-i-break-this-loop-on-a-button-press
 
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage2_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage2_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage2_counter=0;
   

                                      
/*
      // sweep command here

  for (val4 = 0; val4 <= 180 && subpage4_counter==1; val4 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(val4);              // tell servo to go to position in variable 'val4'
    Serial.println(val4);
    delay(500);                       // waits 15ms for the servo to reach the position
  }
  for (val3 = 180; val4 >= 0 && subpage4_counter==1; val4 -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(val4);              // tell servo to go to position in variable 'val4'
    Serial.println(val4);
    delay(500);                       // waits 15ms for the servo to reach the position
  }

      // end sweep
*/
           
                                         
     }  
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage4_counter);  // this shows selector state variable, 0 which is OFF
     // now stop doing it    
     
     }

    }//end void sub menu4 end

//==========================================================================
//==========================================================================
void SubMenuSel_5()
 {   //Design of home page 5 - set Maximum servo position 
     //Static objects 

     lcd.setCursor(0,0);   
     lcd.print("    ");  // clears previous text, 8 gaps
     lcd.setCursor(4,0);   
     lcd.print("Spare");  // this writes "Spare" word, before "angle:"   
     lcd.setCursor(5,1);
     lcd.print(page_counter);
     // ==============================
//  selector button ======SubSelector  is 1 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page============
     // Sub counter 5 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage5_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage5_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage5_counter=0;
     }
     }
     last_sel=current_sel;   
    //  ==================
    //Command item for subpage5_counter=1  
     if(subpage5_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage5_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              val5 = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
              val5 = map(val5, 0, 1023, 1, 180);     // scale it to use it with the servo (value between 1 and 180) 
              myservo.write(val5);                  // sets the servo position according to the scaled value    
              // Serial.println("Menu-1, Manual Servo Control - Enabled");
              Serial.print("SubPage5:");
              Serial.println(val5);
              delay(500); 
              
    // and write cursor position here...using cursorPosition() function to make layout consistant
              cursorPosition(val5);   // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).   
                                      // This way  I can easily change number layout on the screen using the void cursorPosition  

     }  
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage5_counter);  // this shows selector state variable, 0 which is OFF
     // now stop doing it  
     
     }  // else bracket end

  
 
    }//case5 end
    
//==========================================================================
//==========================================================================
void SubMenuSel_6(){   //Design of home page 6 - set Maximum servo position 
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print("    ");  // clears previous text, 8 gaps
     lcd.setCursor(4,0);   
     lcd.print("Spare");  // this writes "Spare" word, before "angle:"    
     lcd.setCursor(5,1);
     lcd.print(page_counter);
     // ==============================
//  selector button ======SubSelector  is 1 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page============
     // Sub counter 6 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage6_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage6_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage6_counter=0;
     }
     }
     last_sel=current_sel;   

    //  ==============================
    //Command item for subpage6_counter=1  ======================================================
     if(subpage6_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage6_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              val6 = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
              val6 = map(val6, 0, 1023, 1, 180);     // scale it to use it with the servo (value between 1 and 180) 
              myservo.write(val6);                  // sets the servo position according to the scaled value    
              // Serial.println("Menu-1, Manual Servo Control - Enabled");
              Serial.print("SubPage6:");
              Serial.println(val6);
              delay(500); 
              
    // and write cursor position here...using cursorPosition() function to make layout consistant
              
              cursorPosition(val6);   // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).   
                                        

     }  
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage6_counter);  // this shows selector state variable, 0 which is OFF
     // now stop doing it  
     
     }// else bracket end

  
    }//case6 end






// =========================================================================
// =========================================================================
void SubMenuSel_7(){   //Design of home page 7 - sMin servo position 
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print(" ");  // clears previous text, 8 gaps
     lcd.setCursor(1,0);   
     lcd.print("Read Min");  // this writes "manual" word, before "angle:"         
     lcd.setCursor(5,1);
     lcd.print(page_counter);
     // ==============================
//  selector button ======SubSelector  is 1 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page=======
     // Sub counter 6 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage7_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage7_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage7_counter=0;
     }
     }
     last_sel=current_sel;   
    //====================
    //Command item for subpage6_counter=1  
     if(subpage7_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage7_counter); // this shows selector state variable, 1 which is ON
     // do this... 
              readMin = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) variable and stores as readMin variable             
              readMin = map(readMin, 0, 1023, 0, 180); // scale it to use it with the servo (value between 1 and 180)                            
              myservo.write(readMin);                  // sets the servo position according to the scaled value    
              sMin = readMin;                          // Now sMin is made equal to readMin.   Only this page uses readMin as a variable and o-180 in the mapping, then all other pages use the sMin variable  
     
              
              Serial.print("This is the readMin value: ");
              Serial.println(readMin);
              Serial.print("This is the sMin value: ");
              Serial.println(sMin);
              delay(500);
              Serial.print("SubPage7:");
              Serial.println(val7);
              delay(500); 

              
    // and write cursor position here...using cursorPosition() function to make layout consistant
              
              cursorPosition(readMin);          // This function writes the servo position to screen and uses the "readMin" amount as its variable (ie degrees being used).   
              sMinCursorPosition(readMin);      // This function writes the MINIMUM servo position to screen and uses the "readMin" amount as its variable (ie degrees being used)                         
              
     }  
     // now stop doing it      
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage7_counter);  // this shows selector state variable, 0 which is OFF
 
     
     }// else bracket end
 
    }//case7 end




//===========================================================================
// ================================
void SubMenuSel_8(){   //Design of home page 6 - set Maximum servo position 
     //Static objects 
     lcd.setCursor(0,0);   
     lcd.print(" ");  // clears previous text, 8 gaps
     lcd.setCursor(1,0);   
     lcd.print("Read Max");  // this writes "manual" word, before "angle:"      
     lcd.setCursor(5,1);
     lcd.print(page_counter);
     // ==============================
//  selector button ======SubSelector  is 1 and locks page-menu item so it cannot change= pressing selecror toggles sub-sel betweem 0 & 1 so 0 releases page============
     // Sub counter 8 control
     if (last_sel== LOW && current_sel == HIGH){ //select button pressed
     if(subpage8_counter <1){                    // subpage counter never higher than 1(total on-off)
     subpage8_counter ++;                         //subcounter to move beetwen submenu
     }
     else{                                       //If subpage higher than 2 (total of items) return to first item
      subpage8_counter=0;
     }
     }
     last_sel=current_sel;   
    //  =================
    //Command item for subpage6_counter=1  
     if(subpage8_counter==1){

     lcd.setCursor(16,1); 
     lcd.print(subpage8_counter); // this shows selector state variable, 1 which is ON
     // do this... 

              readMax = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) variable and stores as readMax variable             
              readMax = map(readMax, 0, 1023, 0, 180); // scale it to use it with the servo (value between 1 and 180)                            
              myservo.write(readMax);                  // sets the servo position according to the scaled value    
              sMax = readMax;                          // Now sMax is made equal to readMax.   Only this page uses readMax as a variable and o-180 in the mapping, then all other pages use the sMax variable  
     
              
              Serial.println("This is the readMax value: " + (String)readMax + "degrees");   // This is a CONCANTONATED STRING
              Serial.println("This is the sMax value: " + (String)sMax + "degrees");   // This is a CONCANTONATED STRING
              Serial.println("This is the SubPage: " + (String)subpage8_counter + " 1:ON 0:OFF");   // This is a CONCANTONATED STRING
              Serial.println("This is the sMin value: " + (String)sMin + "degrees");   // This is a CONCANTONATED STRING
              delay(500);          
             
                
    // and write cursor position here...using cursorPosition() function to make layout consistant
              
              cursorPosition(readMax);         // This function writes the LCD position to screen and uses the "val#" (ie val1, val2, val3 etc) ammount as its variable (ie degrees being used).   
              sMaxCursorPosition(readMax);     // This function writes the MAXIMUM servo position to screen and uses the "readMax" amount as its variable (ie degrees being used)                   

     }  
     else{
     lcd.setCursor(16,1);
     lcd.print(subpage8_counter);  // this shows selector state variable, 0 which is OFF
     // now stop doing it  
     
     } // else bracket end

  
  
    }//case8 end
// ===========================================================================
// ===========================================================================         

/*
 * Relocate "Functions" below here if you do not want to use the IDE Tabs [ie move the cursoPosition, SMax.., SMin.., etc
 * 
 */
//=========================================================
void cursorPosition(int whatval){ // whatval start bracket
                // Servo read out maths go here...
                    if (whatval<10)
                  {
                  lcd.setCursor(16,0);      // COLUMN, ROW  variable read out here over 0 - 9 digits  
                  lcd.print(whatval);           // this shows servo selector value 0-180
                  lcd.setCursor(17, 0);     // COLUMN, ROW  Blank off unused 1st digit if it has prevuously been written.   Other wise there is a"1" left over soo you get 19 not 9 for example
                  lcd.print("  ");          // Two blanks to remove any 10s and 100s digits left over
                  }

                  else if (whatval<100)
                  {
                  lcd.setCursor(16,0);      // COLUMN, ROW  variable read out here over 10 - 99 digits 
                  lcd.print(whatval);           // this shows servo selector value 0-180
                  lcd.setCursor(18,0);     // COLUMN, ROW  Blank off unused 1st digit if it has prevuously been written.   Other wise there is a"1" left over soo you get 19 not 9 for example
                  lcd.print(" ");          // Two blanks to remove any 10s and 100s digits left over
                  }

                  else if (whatval>100)
                  {
                  lcd.setCursor(16,0);      // COLUMN, ROW  variable read out here over 100 - 180 digits  
                  lcd.print(whatval);           // this shows servo selector value 0-180                  
                  }
              }// whatval end bracket



//===========================================================
void sMaxCursorPosition(int readMax){  // function start bracket


                // Servo read out maths go here...
                    if (readMax<10)
                  {
                  lcd.setCursor(16,3);      // COLUMN, ROW  variable read out here over 0 - 9 digits  
                  lcd.print(readMax);           // this shows servo selector value 0-180
                  lcd.setCursor(17, 3);     // COLUMN, ROW  Blank off unused 1st digit if it has prevuously been written.   Other wise there is a"1" left over soo you get 19 not 9 for example
                  lcd.print("  ");          // Two blanks to remove any 10s and 100s digits left over
                  }

                  else if (readMax<100)
                  {
                  lcd.setCursor(16,3);      // COLUMN, ROW  variable read out here over 10 - 99 digits 
                  lcd.print(readMax);           // this shows servo selector value 0-180
                  lcd.setCursor(18,3);     // COLUMN, ROW  Blank off unused 1st digit if it has prevuously been written.   Other wise there is a"1" left over soo you get 19 not 9 for example
                  lcd.print(" ");          // Two blanks to remove any 10s and 100s digits left over
                  }

                  else if (readMax>100)
                  {
                  lcd.setCursor(16,3);      // COLUMN, ROW  variable read out here over 100 - 180 digits  
                  lcd.print(readMax);           // this shows servo selector value 0-180                  
                  }

                  }// function end bracket


//============================================================================
void sMinCursorPosition(int readMin){  // function start bracket


                // Servo read out maths go here...
                    if (readMin<10)
                  {
                  lcd.setCursor(16,2);      // COLUMN, ROW  variable read out here over 0 - 9 digits  
                  lcd.print(readMin);           // this shows servo selector value 0-180
                  lcd.setCursor(17, 2);     // COLUMN, ROW  Blank off unused 1st digit if it has prevuously been written.   Other wise there is a"1" left over soo you get 19 not 9 for example
                  lcd.print("  ");          // Two blanks to remove any 10s and 100s digits left over
                  }

                  else if (readMin<100)
                  {
                  lcd.setCursor(16,2);      // COLUMN, ROW  variable read out here over 10 - 99 digits 
                  lcd.print(readMin);           // this shows servo selector value 0-180
                  lcd.setCursor(18,2);     // COLUMN, ROW  Blank off unused 1st digit if it has prevuously been written.   Other wise there is a"1" left over soo you get 19 not 9 for example
                  lcd.print(" ");          // Two blanks to remove any 10s and 100s digits left over
                  }

                  else if (readMin>100)
                  {
                  lcd.setCursor(16,2);      // COLUMN, ROW  variable read out here over 100 - 180 digits  
                  lcd.print(readMin);           // this shows servo selector value 0-180                  
                  }

                  }// function end bracket


//===============================================================================















