/*
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



*/
