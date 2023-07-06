# Adjustable Blinky

## Description

This project implements a simple LED blinky program that can be adjusted based on an input voltage. The program uses a esp32S3 microcontroller to read the input voltage and adjust the blink rate of an LED accordingly.

## Getting Started

To get started with this project, you will need a ESP32-S3-DevKitC-1 board that supports the required peripherals (ADC, GPIO, etc.). You will also need simple voltage divider including a potentiometer to connect to the microcontroller board.

### Installing

Installing
To install this project, follow these steps:

1. Clone the repository to your local machine.
2. Open the project in your IDE.
3. Get the required framework ESP-IDF for compiling esp32 projects.  
4. Set the target in ESP-IDF to esp32S3. 
5. Build a general esp config. 
6. Build the project using the provided build script for an esp32S3 Target. 
7. Flash the resulting binary to your microcontroller board.
   
## License

This project is licensed under the MIT License.