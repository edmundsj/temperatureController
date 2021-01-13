TEC Temperature Controller PCB
=================================

Issues in Version 1
----------------------
- Need VDD, GND connections on header going to MCP9808 board in addition to SDA and SCL.
- Need to make sure the ordering and connector matches that of the device PCB.
- In the future, a couple of accessible header GND connections would be nice, even just for probing.
- Should edit the silkscreen to include the directionality of the Arduino Nano's USB. 
- Needs a power off button
- My choice of resistor is not sufficient, the thing heats up and starts to smoke after a couple seconds at ~5A. 
- Add a voltage divider to the gate of the transistor - we do not need more than ~4V applied to the gate. Ideally we would also convert the transistor range of ~2.5V-4V into the arduino's 0-5V. We could do this by placing the resistor at the source intsead of the drain of the transistor. This would be a good idea anyway to provide some negative feedback on our current and linearize our transfer function a little. It's possible this is an issue with the supply. I could try and apply a known voltage to the input jack.
- The weird thing is this seems to work pretty well with the USB as a power source up to ~1A, but when I use the power brick all hell breaks loose.
- It looks like the problem probably isn't with the brick, the voltage to the transistor appears to become unstable and starts to oscillate quite a bit. I think part of the issue is the noisy-ass supply
- Closed-loop control of this transistor is proving to be more difficult than I had anticipated, especially given the uncertainty of the parameters involved, and the nonlinearity of the MOSFET. The measurements are also extremely noisy and I think this is contributing to the fluctuations.
- I figured out the culprit - thermal runaway. A small (enough) amount of current heats the MOSFET, which causes the current to rise, which causes the MOSFET to heat more, and on, and on. It's not actually a problem with nonlinearity, just with the MOSFET getting too damn hot. There is instability, but it's not caused by nonlinearity - it's caused by thermal runaway of the MOSFET.
- Thermal runaway WILL be an issue with BJT's as well, since the current gain does increase with temperature (by ~a factor of 3).
- I'm probably going to want to add a small fan and choose a larger transistor package.

Appendix - Debugging PCB
---------------------------
- Looks like everything fits on the PCB! I'm skeptical that the transistor can actually pump 8.5A. The datasheet says it can handle 50W, which seems bizarre. We will see how it holds up in this tiny little package.
- Now time to see how the Arduino nano handles 5V applied from both the USB and the computer. It shuold be fine b/c there's a diode separating them, essentially a 0V resistor at zero bias. Time to start writing code for this badboy.
- When driving all 6 digits, a 10k current set resistor at 3/32 duty cycle is plenty bright. I may want to keep using the 30k resistor for safety.
- The actual current measurement needs to be filtered, because there are some implausibly large measurements that occasionally smack us in the face. Our controller doesn't work well at the level of ~50mA and a load resistance of 50Ohm. It fails completely.
- Actually, this doesn't appear to be an issue with the controller, but with the sensitivity of the transistor to the unfiltered PWM. I am going to need a more aggressive filter to eliminate this, at the cost of slower dynamics. I'm going to move to a 10k resistor instead of a 1k resistor, which still gives a 100ms time constant, very fast for what I am doing.
- In the process of testing my PCB at some point the display stopped working and now all the digits are lit up, even the colons. It's unclear why this happened, but appeared to be fixed by power cycling the thing. Looks solid. I think we are ready to test on the actual TEC.
- Testing with the TEC, when injecting positive current into the red terminal, the top of the TEC definitely gets cooler than the bottom. My control system also appears to work. NEAT! Now I need to see what happens when I plug the thing in.
- NEAT! That works too!!! Looks like I can even plug it into both the computer and the power brick. It would be nice to have a power reset button so I don't have to plug anything.
- Well looks like I almost certainly fried my resistor at a forward current of ~5A. I got some magic smoke. I should definitely turn my PI controller into a PID controller. There is hella overshoot. I need to make sure that the filter is faster than the PI controller, otherwise I'm going to screw myself with overshoot. It's time to more carefully analyze the stability of this system. Once I get the current control working then I can move onto the outer temperature loop. Surprisingly the transistor seems to handle this like a champ. Might need a different resistor, though.
- Now for some reason the arduino has become inaccessible over the port I was using to communicate with it. Very odd. Too much current?
- For some reason even plugging in the high-current source makes everything freak out. 
- Time to do a high-current test. Yup, that was a miserable failure. Pretty sure I fried something. For some reason the current overshoots to ~5A and then refuses to fall back down. 
