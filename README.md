### Arduino Audio Library for Adafruit Feather M0 Express SAMD21

A branch of the SamdAudio library https://github.com/hydronics2/SamdAudio/

This polyphonic library allows you to play WAV files from SPI Flash to the 10bit DAC of a SAMD21 (Pin A0 on many boards). 
Plays up to ~4 WAV files simultaneously.

For use with SD cards refer to https://github.com/hydronics2/SamdAudio/

Adafruit has a nice tutorial on how to connect the pin to a 1/8" audio jack. The hookup [instructions are here](https://learn.adafruit.com/circuitpython-essentials/circuitpython-audio-out) (ignore the circiut python example as this library is for an Arduino sketch).
![Adafruit image](https://cdn-learn.adafruit.com/assets/assets/000/057/479/original/circuitpython_ItsyBitsyM0AudioJackButtonPot_bb.jpg?1531328765) 

The 8bit sound quality is medium quality. I was able to get up to 44.1khz using SPI flash on the Adafruit M0 boards. The quality needed to  be reduced to ~22khz when playing from the SD card.

I use it with an Adafruit Mono 2.5W Class D Audio Amplifier - PAM8302 https://www.adafruit.com/product/2130
Note that you may have to turn the volume down, using the onboard trim potentiometer for adjusting input volume, or it may overdrive the speaker.

The following Adafruit Express boards have onboard FLASH where you can store up to 2MB of sound ~30-120seconds depending on the sample rate.
This includes: 
* [Itsybits M0 Express](https://www.adafruit.com/product/3727) (tested)
* [Adafruit Metro M0 Express](https://www.adafruit.com/product/3505) (tested)
* [Trinket M0 Express](https://www.adafruit.com/product/3500) and Gemma Express no SPI Flash so SD card playing only. 

NB: Adafruit M4 Express boards with the SAMD51 will not work with this audio library


Read this great description in the Adafruit tutorial for getting the WAV files onto your Adafruit M0 Express board
https://learn.adafruit.com/introducing-itsy-bitsy-m0?view=all#using-spi-flash 
Thanks to Tony Dicola and Adafruit for making this so easy!

Flash example included in the examples folder. 
