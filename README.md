# Arduino-projects
Arduino-projects
> **Note on Language:** The user interface, variable names, code comments and file names are written in Italian.

## Material used
- **Bad USB:** Arduino UNO R4.
- **Bluetooth:** Arduino UNO R4.
- **RC_Car:** Arduino UNO R4 (for the car), Arduino UNO R3 (for the controller), Joystick, 2 radio frequency modules nRF24L01 (TX:controller, RX:car), motor drivers L298N, 2 electric motors, chassis with wheels supplied.
- **Scritta scorrevole display lcd:** Arduino UNO R4, dislpay lcd 2x16.
- **ROBOSUMO:** Arduino Nano, robot mBlock, ultrasonic sensor HC-SR04, infrared sensor TCRT5000, 2 servomotors SG90

## Functionality
- **Bad USB:** Arduino simulates a keyboard and types commands into the computer.
- **Bluetooth:** Bluetooth connection between Arduino and smartphone.
- **RC_Car:** Design and development of a radio-controlled car. Source code `codice_macchina.ino` is used to control the motors and the receiver module; source code `codice_controller.ino` is used for the joystick.
- **Scritta scorrevole display lcd:** Scrolling text on a LCD display.
- **ROBOSUMO:** A self-driving robot car used for combat in an arena. The phone connects via Bluetooth to the Arduino Nano, and based on the input, the servomotors raise or lower a bucket.

## IDE
- Arduino IDE
- https://ide.mblock.cc/
