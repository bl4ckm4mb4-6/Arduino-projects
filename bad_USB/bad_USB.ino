#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_it_IT.h>

void setup() {
  delay(2000);
  Keyboard.begin();
  for(int i=0;i<3;i++){
    delay(500);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(500);
    Keyboard.print("notepad");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.print("Sei stato hackerato");
    Keyboard.releaseAll();
  }
  Keyboard.end();
}

void loop() {
    
}
