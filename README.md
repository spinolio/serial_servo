Control a servo with simple commands over serial connection. Several commands can be entered in the Aurdino serial monitor before sending. The commands are:

- l: left
- r: right
- c: center
- p: pause

The code is written with and LED connected to pin D9 and the servo control signal connected to pin D10. Servo motion at the time of this commit was from
30 to 150 degrees.

The code disables the servo control signal after moving to eliminate servo chatter and wear. This works fine with my example servo, but some 
servos might be different and move to some default position if no control signal is present. That would require leaving the servo control
signal attach'ed continuously.
