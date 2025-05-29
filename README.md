# Voice Controlled Smart Home using ATmega32
A smart home system based on the ATmega32 microcontroller that allows voice or text command control through USART. It includes device control (lights, fan, servo-controlled door), user authentication, and sensor-based automation.
## 🔧 Features

- ✅ User authentication via USART
- 🎤 Voice/text command interface (PC or Bluetooth)
- 🚪 Servo motor control for door opening/closing
- 🌡️ Room temperature monitoring with LM35 and LCD
- 💡 LDR-based auto/manual light control
- 🌬️ fan control

## 🧰 Hardware Components

- ATmega32 Microcontroller
- LEDs
- 16x2 LCD Display
- LM35 Temperature Sensor
- LDR Sensor
- Servo Motor
- DC Motor 
- Push Buttons
- Bluetooth Module 
- Power Supply

## 📁 Project Structure

Voice_Controlled_SmartHome/
```
|-- main
|   |Project.c
|   |Project.h
|-- MCAL
|   |-- DIO
|   |-- PORT
|   |-- GIE
|   |-- ADC
|   |-- UART
|   |-- TIMERS
|
|-- HAL
|   |-- LCD
|   |-- LCD 
|   |-- DC_MOTOR
|   |-- SERVO_MOTOR
|   |-- LM35_Sensor 
|   |-- LDR_Sensor
|
|-- LIBS
|   |-- BIT_MATH.h
|   |-- STD_TYPES.h
|   |-- MAP
|   |-- ErrorType
```

## 🚀 How to Use
1. **Build and Flash Code**:
   - Use Atmel Studio or AVR-GCC toolchain.
   - Upload firmware to ATmega32 using USBasp or a compatible programmer.
2. **Connect via USART**:
   - Use a serial terminal Bluetooth module.


  ## 💡 Example Commands

| Command                | Function                      |
|------------------------|-------------------------------|
| `LOGIN 1234`           | Authenticate the user         |
| `open the door`        | Open the servo motor door     |
| `auto light intensity` | Enable auto light mode (LDR)  |
| `switch on the fan`    | switched the fan on           |



## 🙋‍♂️ Author

Developed by [Mohamed Salah Owida](https://github.com/Mohamed-Salah-Owida)


