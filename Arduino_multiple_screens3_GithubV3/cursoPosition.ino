/*
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

*/
