# Music-Reader
 
I wanted to give myself a challenge with c++, so I decided to make a program that reads music off of "https://pianoletternotes.blogspot.com/". The program automatically calculates delay between the next note by calculating the amount of dashes between the current and the next note. BPM and lane size is defined at the top of the text files - there are two included example sheets: Music_sd and Music_bv.

As the program uses the Beep() function, the program is incapable of harmonising two or more notes at once. The example sheets have been edited to remove these notes, but if you were to copy and paste straight from the website mentioned above, the program and music should run without any problems.