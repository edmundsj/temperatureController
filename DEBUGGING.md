Test Data
-----------
- Version 1 is able to drive current of <100mA using closed-loop control and a 5V USB supply, but is unable to drive higher currents due to thermal runaway.
- Version 2 is able to drive at least +/- 4.5A with the main heatsink rising to 60C. TEC temperature control works over range of 1C - 80C with response time of ~10s and overshoot of 30%. 

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

- Add a voltage divider to the gate of the transistor - we do not need more than ~4V applied to the gate. Ideally we would also convert the transistor range of ~2.5V-4V into the arduino's 0-5V. We could do this by placing the resistor at the source intsead of the drain of the transistor. This would be a good idea anyway to provide some negative feedback on our current and linearize our transfer function a little. It's possible this is an issue with the supply. I could try and apply a known voltage to the input jack.
- The weird thing is this seems to work pretty well with the USB as a power source up to ~1A, but when I use the power brick all hell breaks loose.
- It looks like the problem probably isn't with the brick, the voltage to the transistor appears to become unstable and starts to oscillate quite a bit. I think part of the issue is the noisy-ass supply
- Closed-loop control of this transistor is proving to be more difficult than I had anticipated, especially given the uncertainty of the parameters involved, and the nonlinearity of the MOSFET. The measurements are also extremely noisy and I think this is contributing to the fluctuations.
- I figured out the culprit - thermal runaway. A small (enough) amount of current heats the MOSFET, which causes the current to rise, which causes the MOSFET to heat more, and on, and on. It's not actually a problem with nonlinearity, just with the MOSFET getting too damn hot. There is instability, but it's not caused by nonlinearity - it's caused by thermal runaway of the MOSFET.
- Thermal runaway WILL be an issue with BJT's as well, since the current gain does increase with temperature (by ~a factor of 3).
- I'm probably going to want to add a small fan and choose a larger transistor package.

Version 2 Experiments
_______________________
Prediction (P): Using a proportional only controller with a value of Kp, we should see the steady-state error of the system be kp / (1 + kp), and the 95% settling time should be (1+Kp) times faster than the settling time of the filter.
Prediction (PI): Using a PI controller, we should see zero steady-state error, and for a given Kp, we should see the dynamics improve by decreasing ti (the integral time) until about wi = wL/4 * (1+Kp)^2. where wL is the frequency of the lowpass anti-aliasing filter. At this point, the characteristic frequency  of the overall system is given by wL/2 * (1+Kp) assuming zeta=1 (critical damping).
Prediction (PI): Since we are using PWM, our error will not be zero even when it *should* be zero. We have an extra sinusoid riding on top of that. This could lead to instability of the system if the anti-aliasing filter is not low-frequency enough. Specifically, we need that fL^2 * Kp^2 / (fs*fPWM) be less than 1, and we need to pray that our PWM is aliased to a reasonably high frequency compared to the sampling frequenncy. This places a restriction on Kp. and our ultimate dynamic performance, giving us a maximum natural frequency of fs*fPWM/(2*fL), where fs is our sampling frequency. For a 1Hz lowpass filter, a 1kHz PWM frequency, and a 20Hz sampling frequency, the maximum time constant we can achieve is ~20us, which means we should have plenty of margin to avoid instability.
We can create a PI controller by setting the current output at time n to equal
In = I(n-1) + Kp*(Ierr(n) - Ierr(n-1)) + wi*dt*Ierr(n)
Where I(n-1) was the previous current, Ierr is the measured minus the desired value of the current, dt is the time between samples, wi is the integral gain (in frequency form)

- When testing the TEC controller with a 10k base resistor and a multimeter to measure the current, it is able to drive up to 4A without issue. Around 4A I heard a popping sound from the TEC, and I'm not sure what caused that, but it feels very hot on both sides. I suspect I may have gone above its rated voltage. This time, though, no issues with thermal runaway, which is encouraging. It's possible the TEC is getting a higher voltage dropped across it than intended. I really need to attach it to a heatsink so I can see if it's actually cooling one side. The whole thing is definitely heating up, which should be expected. Now to stress test the whole system.
- The display output is currently pretty meaningless. 
- I really need a way of thermally connecting objects in a permanent but reversible way. Some thermal tape or something. Double-sided copper tape could actually do a reasonable job of this, where is mine? Next time I'm home I should grab the copper tapeo
- For now, I'm just going to use silver epoxy and assume the TEC will be permanently attached. I have another one if needed.

Temperature Test
___________________
- Room temp is measured to be 23.6C.
- Looks like my on-board measured current is way higher than what my multimeter is reading - it might be giving peak current and not average current? I don't know.$
- After we got above 600mA, the current started giving expected values again. I expect this is an ADC biasing issue. After increasing the current again, the measured current is again all over the place. It's down to 350mA. I might just need a better ADC.
- Now at 750mA we are measuring 210mA, this is absolute and utter nonsense. I need a better way of doing this. The present way of measuring current seems to be worse than useless. Perhaps it's an aliasing issue?
- At 1A the main heatsink isn't heating up much. Current is quite stable over time (within a few mA) less than 1A.
- Above 1A, the current is starting to fluctuate some more, +/- 20mA max.
- At 1.4A, the on-board heatsink is starting to heat up to become uncomfortably warm to the touch.
- We are able to reach a temperature differential of 45C so far at 1.5A going in the warm direction. Excellent so far. I'm going to shoot for 70C or 3.5A DC, whichever comes first.
- The current is starting to fluctuate a little more.
- At 1.6A the heatsink is still warm to the touch, but not excessively so. The measured current is 1.14A, about 50% off. I think I'm just asking way too much of the poor nano's ADC.
- At 1.9A the heat sink is getting warmer, but it's doing it's job.
- At 2.02A, I heard a weird sound I think from the TEC. This corresponded to a delta T of 63C, very close to the max rating for the TEC, so I stopped and cooled the thing down.
- The Al heatsink I attached this thing to doesn't feel significantly hotter. I am now going to change the polarity of the current.
- Room temp is measured to be 23C by an external temp sensor.
- Looks like the heatsink did heat up by ~5C during operation. I may have to pay close attention to thermal management of the TEC itself, as it is dissipating power.
- I am going to wait for the heatsink to cool down closer to 23C, then do the experiment in the reverse direction.
- The TEC appears to be broken in the reverse direction - reverse current isn't doing much at all to decrease the current. This may have been the result of my earlier mishap.
- This is not working. I'm going to go up to 2A and see what happens.
- At -3A, it only gets down to ~16C. I think it's broken.
- At -3.6A, it's down to 11C. Not nearly cold enough. I had the text facing up for this experiment.
- On the upside, the PCB has no trouble sending 3.6A, although this is as high as we can go at 100% duty cycle with a 10k resistor going to the base of the transistor. I'm going to try swapping out the TEC. Current flowing into the red wire is the problem configuration.
- Heatsink gets uncomfortably hot after a couple of minutes, nylon screw is holding, nothing is on fire.
- Above ~2A the ADC is actually quite accurate.
- The TEC appears to increase the heatsink temp during operation by ~3-4C. Time to crank up the volume, increase the current to the max rated value. Also see how my PCB handles ~6-7A. The other TEC is almost certainly damaged.
- Looks like I cannot get below ~1C due to self-heating of the TEC. At 4.25A the PCB heatsink is getting very hot to the touch, but no magic smoke. After a couple minutes the temperature is going up, now up to 3.5C. Now we're up to 5C. According to my IC, the temp is 60C at 4.2A. The current has only been reduced by ~50mA over ~10min. I can try driving the TEC even harder, up to 8A, with a smaller base resistor. I can go down to 1k. The PCB itself does not feel like it is heating up.
- The Al heatsink temp has increased to 33C from 23C. The heatsink I am using needs to do a better job staying at room temperature.
- with a Kp of 0.1, the overshoot for a target of 33.9C in heat mode was 0.8C, and it takes awhile for the controller to get down to 33.9, I suspect due to self-heating of the TEC. Larger Kp would be better.
- A Kp of 0.3 is faster with no stability issues.
- A Kp of 0.9 is even faster and has ~2C overshoot, which is very much acceptable. Let's now tune Ti.
- A Ti of 300ms is too fast - I get some instability. I should also consider restricting the current on the positive direction.
- A Ti of 700ms gives a 3C overshoot, followed by an 0.7C undershoot, followed by a 0.3C overshoot. For a 1C rise, there is a 0.3C overshoot. This is more than acceptable.

Debugging Version 3
____________________
- First, let's check whether the TEC is appropriately connected when everything is off. TEC_H should be connected to VDD, and TEC_L to VSNSH. This is indeed the case. The displays are also being driven properly, and the temperature readout is nominal (23.3C). The pot is working as well. Now time to check the voltages. VDD/2 is 2.35V, and everything else is behaving properly. Now I need to modify the code to give a readout of current.
- For some reason, there's significant nonlinearity in the current. Before we get to some threshold duty cycle, the current is very close to zero. Are we using the right transistor? A BJT should be perfectly linear.
- The current drift is also pretty extreme - from 700mA, the current is rising to over 1A without doing anything to it. This was not typical behavior on the previous board. The current continues rising, it's up to 1.2A, when I'm driving with a duty cycle of 66/255 and the heatsink doesn't feel like it's even getting warm. At least the current sensing mechanism is working :) It's accurate to within ~100mA. The current has now risen to 1.4A, and continues to rise. Now it's at 1.5A. The relay doesn't feel warm to the touch at all. The current continues to rise. Now it's at 1.7A, and the heatsink is getting considerably warmer. Turning the duty cycle down to 58/255 pushes the current down to 500mA, and now it's starting to fall. This smells like a temperature issue. But why was it not present in the last PCB? I need to measure the voltage across the drive resistor, and Vbe to see what doesn't make sense. Now the current is down to 280mA.  Now down to 150mA
- The measured voltage at the base of the transistor has a 1.1V offset, and there is a transient rise of about 100mV across our 1k resistor. This is really weird - the direction of the current appears to reverse. During duty cycling almost all the volage is dropped across the resistor. Perhaps this has something to do with the capacitor I added at the input, C4? This wasn't there before. Here's my hypothesis. It looks like the capacitor is maintaining the voltage at the base at a very high value, so what we really have is exponential (voltage from base to emitter) control of our BJT. C4 should not exist, it was a terrible idea to put it there in the first place.
- This also explains why there's so much temperature drift - we're getting the e^{-1/kT} dependence on voltage rather than the hFE vs. temperature dependence.
- Now the displays are flickering and the arduino isn't responding to commands. This is because the TEC is transiently drawing too much current during duty cycling. I will need to separate the TEC voltage supply from the arduino voltage supply in future versions. This will allow me to use other voltages and other TECs as well.
- When I connect the TEC something is making a really annoying high-frequency sound. WOAH. This appears to be due to making a connection to the TEC itself. The contact gap is making the sound. The 1k resistor looks good, it gives up to 3.5A at a voltage of ~140. Now time to implement current control and temperature control. The current also looks good, tracking the actual current within ~20mA of the actual value over the range 0-4A.
- For some reason the displays decided to have a heart attack and were all zeros. Re-uploading the code fixed this- At very low duty cycles our current measurement is not working well at all. It's oscillating all over the place. I think this is because we're now measuring a pulsed current, and our filter is not nearly aggressive enough. Personally I think we just bypass current control altogether.
- For some reason, my controlTemperature() function is crashing the arduino. Everything is hanging after that function.
- It appears to be the digitalWrite() command that is crashing the system. This is truly baffling. I can hear the relay clicking. Here's my guess - our transistor is not having a voltage applied to its gate, but we are actually applying a voltage directly to the relay. It takes up more current than our pins can drive and could potentially lock out our arduino.
- It looks like when I write the pin HIGH on a blank sheet of code, everything works just fine. There must be something conflicting with this? The serial monitor appears to be a cause of the issue.
- At 1kOhm we can drive a maximum of 4.6A of current, which gets us down to about 7.7C. The heatsink the TEC is attached to is definitely getting a little warm.
- The CPU heatsink is getting warm to the touch, we are now only able to get down to 13.3C at 4.6A. Do we want to go up in drive current? Everything here is rated for 8A, so it would be kosher. Looks like the actual temperature of the heatsink when we were driving the other side of it to 15C is at least 35C - about 12C above room temperature. If we want to get <10C, we're going to have to actively cool the CPU heatsink, either with a fan or liquid.
- The simplest way of mounting this heatsink is just to adapt the heatsink I currently have via a <25mm diameter, >1.5cm height cylinder and attach it directly to the backside of my existing cage system. I'll ask the machine shop what they have. In the meantime, I bought a fan. Should help to keep the heatsink cool.
- For a 10C positive step, the 90% rise time with Kp = 0.5, Ti = 0.7s is ~50s, and the 1% settling time is 1min50s. Let's try increasing the I. With Kp o* 0.5 and Ti of 0.3, there is a 2C overshoot and then a 1C undershoot, and the total 1% settling time is about 1min20s. Going from 30C->20C there is a 3 degree overshoot, which bottoms out by 35s and starts to increase.

* Rise time to 90% of the target value
** Settling time to within 0.1 degree of the target value, equivalent to 1% settling time.

- The temperature setpoint is drifting around like crazy, and the displays are sometimes dimming. It doesn't seem to have anything to do with the relay, but I suspect it's drift of the voltage source itself used to supply the potentiometer I'm using. This is pretty annoying and will make it more difficult to interpret results. Found the problem - the damn supply wasn't plugged in, it was using USB power.

Looks like the max current is 4.6A, which corresponds to a Vce of about 1V, a drop across our resistor of about 1V, and a drop across the TEC of 3V. The constraining factor I did not account for is Vce of the transistor.
