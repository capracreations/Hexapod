# Hexapod
## Overview
![](/images/hex2.jpg)  
Six-legged articulated robotic walker which can be controlled with a gamepad through 2.4GHz transceivers. The Hexapod uses 18 MG996R 9-13kg/cm at 5.0V.

## Please Read
The code and files within this repository are currently a **_WORK IN PROGRESS_** and as such I cannot ensure that all the code provided will be in a usable/stable form as I can only work on it during my free time. The design of the Hexapod has not been finalized and is subject to change and modification at any time. Please refer back to this repo from time to time for code and model updates if available. All external resources used (except for product pages) have been referenced within the **_resources_** below, please refer to them for additional info. **_Ryan Mirch's_** hexapod code is used to assist logic and structure within parts of my code; See **_resources_** below for repo.

## Requirements
This project can be a bit lengthy and may test your skills -as it has mine- in design, electronics and code logic, and such it is necessary to be prepared for the task, below is a list of softwares and equipment that will be required to create your own hexapod.
### Softwares
- CAD Software (Solidworks, Fusion360, Onshape)
- 3D-printing Slicer (Cura, Prusaslicer)
- Arduino IDE 2.0 or higher
### Hexapod
- 3D-printer
- 4kg PETG filament, any brand and colour(s)
- Arduino Mega
- 18x MG996R 9-13kg/cm Servos
- NRF24L01 2.4GHz tranceiver module
- Hexapod Arduino PCB Shield (See **_Arduino Ant Hexapod_** in resources for PCB files)
- 12V to 5V Buck DC converter
- 11.1V (3 Cell) Lipo battery
- M.# bolt and nut set
### RF Controller
- Arduino Nano
- NRF24L01 2.4GHz transceiver module
- 2x PCB joystick modules
- 3x PCB push buttons
- 2x PCB slider potentiometer modules
- Switch (2-pins)
- 9V battery

## Inverse Kinematics Solution
Written and worked inverse kinematics solutions for one leg are provided for clarity and understanding. The solution has already been implemented within the code.

## .STL 3D Model Files
.stl CAD files for the Hexapod and RF Controller are provided for download, parts are designed and toleranced to be **_3D-printed_**. The Hexapod is composed of two main body parts, and six legs with three segments each. Each leg has three rotational joints to allow for a sufficient range of motion.

## Hexapod PCB
For the hexapod to function, a custom Arduino Mega shield is required which can support and drive 18 servo motors at once. How to Mechatronics has already done the hard work for us this time by providing a PCB which can drive up to 24 servos at once, and the files can be downloaded from section 6.1 on their website; see **_Arduino Ant Hexapod_** in the resources below. I also recommend that you read through the page to learn more than I can say about assembling the overall circuit. The PCB can be ordered online from PCBWay or JLCPCB (not sponcered by either), if you're worried about messing up while soldering do not worry as they will send you 5 copies.
![How To Mechatronics's servo shield](/images/hexapod_pcb.png) 
### Resistors
- R1 = 2KΩ
- R2 = 1KΩ
- R3 = R4 = 220Ω
- R5 = 1KΩ
- R6 = 2KΩ
### Capacitors
- C1 = C2 = 10V/470μF
- C3 = 10V/47μF

## Arduino Code Files
For ease of use and to limit confusion please note that the main code is always assigned the **_.ino_** file type. All **_.h_** and **_.cpp_** type files are **_declarations and definitions_** for objects or functions used within the main **_.ino_** code. To be able to use the code in a "plug and play" style, download the entire root file as a .zip and extract to where desired. From there open the main **_.ino_** file within "Arduino Code/Hexapod" as is and it will ask if you want to create and store the **_.ino_** file in a folder of its own name. Select "yes" and transfer the **_.h_** and **_.cpp_** files into the created directory and they should be applied to the main file automatically.

## Resources
-[Ryan Mirch's Hexapod Repo](https://github.com/Ryan-Mirch/Aecerts_Hexapod_V1/tree/main/Hexapod_Code)  
-[Arduino Ant Hexapod](https://howtomechatronics.com/projects/arduino-ant-hexapod-robot/#h-assembling-the-pcb)  

