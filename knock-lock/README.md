# Knock Lock

This is my own take on the starter kit's 12th project, "Knock Lock." It keeps track of the time between knocks to hard-code unique knock sequences.

There are 3 LEDs and each time a knock is detected, the LEDs alternate between which one is turned on. When all the knocks are executed with the correct timing, all 3 LEDs turn on. The variable `isInTestMode` can be used to display the time between knocks to program a new knock combination.

The knock combination can be changed to any number of knocks with any timing between them by modifying the `knockIntervals` array.

<img src="./media/project.JPG" width="300" />
<img src="./media/knock.gif" />
