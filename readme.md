# TCP/IP project #

    Projects that demonstrate labview and C programming  skills 

- [TCP/IP project](#tcpip-project)
  - [Main objectives](#main-objectives)
    - [Server - Raspberry Pi 4B](#server---raspberry-pi-4b)
    - [Client - LabVIEW (PC)](#client---labview-pc)
    - [Electrical diagram](#electrical-diagram)
  - [LabVIEW](#labview)
    - [Three state of work](#three-state-of-work)
    - [Data analysis - LabVIEW](#data-analysis---labview)
    - [SubVI](#subvi)
    - [Client - Labview TCP/IP structure](#client---labview-tcpip-structure)
  - [Raspberry Pi](#raspberry-pi)
    - [Funcions](#funcions)
    - [Server - C socket structure](#server---c-socket-structure)

---

## Main objectives ##

 Client-Server architecture

### Server - Raspberry Pi 4B ###

- program written in C language
- user sets port while calling the main function (must be one number)
- Temperature measure using DS18B20 (1-wire interface)
- "Write" 5 bytes to client (LabVIEW) and shown on the graph in real time
- "Read" 3 bytes using to turning ON/OFF LEDs

### Client - LabVIEW (PC) ###

- program written in G (graphical) language
- Reading bytes from server and converting to temperature in Celsius
- Selection of one of three operating modes
- Data analysis

### Electrical diagram ###

- Raspberry Pi 4B+
- DS18B20
- 1x 4k7Ω
- 3x 1k1Ω
- LED: red, yellow, green

![electrical](raspberry/electrical.png)

---

## LabVIEW ##

LabVIEW code explain

### Three state of work ###

- normal
  - below the programmable variable (name: warning)
  - green lamp (VI and led)
- warning
  - between the first and second variable (name: warning and danger)
  - yellow lamp (VI and led)
- danger
  - above "danger" variable
  - red lamp (VI and led)
  - danger cannot be lower then danger (in this situation the variable is set to: warning + 1 )

### Data analysis - LabVIEW ###

- max temperature value
- min temperaturevalue
- average temperature value
- all values during the program
- saving all values (location programmable set to VI path - on button click)
- clearing data (waveform Chart and values in array on program start or on button click)
  
### SubVI ###

- temperature_from_string - temperature calculation
- state - state set and sending string to server, correcting *danger* value
- mean - calculation: *average, max, min value*
- saving - saving data

### Client - Labview TCP/IP structure ###

 1. Open conection
 2. Read and Write
 3. Close conection

---

## Raspberry Pi ##
  
Raspberry Pi code explain

### Funcions ###

- main() - main funcion
- IsNumber() - checking if the given value is a number
- WiringPi() - Initialize WiringPi and GPIO
- Temp() - reading values by 1-wire
- Lamps() - turn ON/OFF LEDs

### Server - C socket structure ###

 1. Create socket
 2. Bind
 3. Listen
 4. Accept
 5. Write and Read
 6. Close
