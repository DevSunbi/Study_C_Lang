#include <wiringPi.h>
#include <iostream>

int main() {
    int retValue = wiringPiSetup();
    if (retValue == -1) {
        std::cerr << "wiringPi setup failed!" << std::endl;
        return 1;
    }
    pinMode(29, OUTPUT); // Set GPIO pin 29 as output
    pinMode(28, INPUT);
    int cnt = 0;    
    while(1)
    {
        if(digitalRead(28) == 1) // Check if the button is pressed
        {
            std::cout << "btn pressed" << std::endl;
            digitalWrite(29, 1); // Turn on the LED
            cnt++;
            delay(100);
        } else {
            std::cout << "btn not pressed" << std::endl;
            digitalWrite(29, 0); // Turn off the LED
            delay(100);
        }
        if(cnt == 10) {
            std::cout << "btn pressed 10 times" << std::endl;
            break; // Exit the loop after the button has been pressed 10 times
        }
    }

    return 0;
}
