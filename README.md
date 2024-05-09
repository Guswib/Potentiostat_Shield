# Potentiostat Shield for Arduino Uno
The is project is a piece of software to run a Potentiostat shield on a Arduino Uno.


## Background
A potentiostat/galvanostat is a device used to control electrochemical experiments. It can control either voltage or current between 2 or 3 electrod. For more infomration see the following links. 

* [Wikipedia Potentiostat](https://en.wikipedia.org/wiki/Potentiostat)
* [Wikipedia Galvanostat](https://en.wikipedia.org/wiki/Galvanostat)

## The Potentiostat Shield
In the software, the following signals from the arduino is used by the potentiostat shield in order to make a function potentiostat:

* D5 - Cell Switch
* D6,D7 - Current Range
* D10,D11,D12,D13 - SPI
* A0 - Virtual Ground (50% of Vcc)
* A1 - Voltage of the reference electode
* A2 - Voltage of the Current converter(IE)

### How it works

A potentiostat works with signed voltages and currents. As the arduino uno can only measure and support 0-5V, a virtual ground must be introduced which is at 2.5V(50% of Vcc). 
The current-to-voltage converter(IE) is connected to the working electrode. It measured the current and keeps the working electrode at the potential of the virtual voltage. The potential of the working electrode(E) is the voltage different between reference electrode and the working electrode. In order to obtain this value, the arduino must first measure both virtual ground and the voltage of the reference electrode, then calculate the difference between the values. Similarliy,  the current signal is to be measured. 

 




## The Potentiostat Shield - DIY solder
This potentisotat shield was developed in order to used as few and easy to solder(DIP package) components as possible in order to turn an arduino UNO into a potentiostat/galvanostat. 
The potentiostat has different has a cell switch and 4 different current ranges. The control signal is generated by a SPI DAC, while the voltages are measured using ADC of the arduion.

### Potentiostat Shield Schematics

The following image shows the schematics of potentiostat shield.

![Potentiostat Shield Schematic](/assets/images/UNO_Pot_Shield_1_1_schematic.png)

Higher resolution image be seen in the [PDF](Schematic%20Design_%20UNO_%20Pot%20Shield_1_1.pdf)

 

### Potentiostat Shield PCB

The following image shows the potentiostat shield PCB.

![Potentiostat Shield PCB](/assets/images/UNO_Pot_Shield_1_1_s.png)


[Potentiostat Shield PCB with higher resolution](/assets/images/UNO_Pot_Shield_1_1.png)


### Compoents (BOM)
 * DAC MCP4921 1x
 * MUX DG409 1x
 * OPA-2ch MCP607 1x
 * Screw Terminal-3x    
 * Resistors
   * 100 Ohm 1x
   * 1 kOhm 1x
   * 10 kOhm 6x
   * 100 kOhm 1x
   * 10 MOhm 1x
 * Capacitors
   * 10 nF 1x
   * 100 nF 3x
   
  "/?", "CELL", "CMODE", "IE", "SET", "ABORT","HALT","DEBUG","RAMP", "VGND","STEP"
