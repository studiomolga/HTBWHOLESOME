# HOW TO BECOME WHOLESOME - CIRCULATING WATER PUMP SYSTEM

## ASSEMBLY

### Connect arduino to pwm controller
- Take the arduino, the pwm controller board and the cable as show in the image, the cable has two distinct sides, one with two male connectors that will go the arduino and one with a single female connector that will go the pwm controller. The pwm controller is the blue pcb with a right angled header on the side. 
- Connect the cable as show in the two images, please note the orientation of the cables.

#### pwm cable
![pwm to arduino cable](/images/pwm_cable.jpg)

#### cable to arduino i2c
*please note the orientation, and make sure that the correct pins are used*
![cable to arduino side i2c](/images/i2c_to_arduino.jpg)

#### cable to arduino vcc
*please note the orientation, and make sure that the correct pins are used*
![cable to arduino side vcc](/images/vcc_from_arduino.jpg)

#### cable to pwm
*please note that the blue line aligns with the pin labeled GND*
![cable to pwm side](/images/pwm_to_arduino.jpg)

### Connect pumps to motor drivers
- Take the power assembly, which is the black junction box with wires connected to it. On one side you find a power plug, leave this UNCONNECTED until the very end. The other side has cables connected which end in a small pcb, these are the motor drivers. Also take out the pumps. The pumps also have wire solderd to them.
- connect the wires of the pumps to the empty slow on the screwterminal on the motor drivers as shown in the image.

### Connect mmotor drivers to the pwm controller
- Take the 4 jumper cables.
- Connect the cables to the pwm controller as shown in the image. You will need to use ports: 0, 1, 2, 3. Also please note the orientation of the cables in the image, if for some reason one of the pumps pumps the wrong way, flipping the orientation over will fix that.
- Connect the other end of the jumper cables to the motor driver, please make sure that you use the two pins labeled `IN1` and `IN2`. See the image.

### Connect arduino to power assembly
- find the DC barrel jack connected to the power assembly and connect to arduino as shown in the image.

### Finalize
- Go over everything again and make sure its connected properly
- Connect the powerplug to a wallsocket, please note, its a European powerplug so and extension might need to be used.
