/*
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



*/
