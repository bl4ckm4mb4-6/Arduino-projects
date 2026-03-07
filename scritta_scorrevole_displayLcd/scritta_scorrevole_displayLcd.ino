#include <LiquidCrystal.h>
#include <string.h>

const int rs=12, en=11, d0=7, d1=6, d2=5, d3=4;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

String nome="Perrino";
int c=16;
int i=0;

void loop() {
  c=16;
  i=0;
  for(c=16;c>=0;c--){
    if(i<nome.length()){
      lcd.setCursor(c, 0);
      lcd.print(nome);
      delay(500);
      i++;
    }
    else{
      lcd.clear();
      lcd.setCursor(c, 0);
      lcd.print(nome);
      delay(500);
    }
  }
  for(i=1;i<=nome.length();i++){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(nome.substring(i, nome.length()));
      delay(500);
  }
}
