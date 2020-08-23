/*

  Audio player, non blocking.
  read 8bit mono .wav file, up to 4 channels
  use Audacity to convert your audio file
  Author : AloyseTech with subsequent modifications by various people including,Hydronics and Gambalunga

  03/17/19: https://github.com/hydronics2/SamdAudio
    updated to work with Adafruit Qaud Flash memory boards.
    This will work with any SAMD21 chip using SPI flash with a little tinkering
     - itsyBitsy M0 Express,
     - Feather M0 Express,

   23/07/2020:
    updated to work with the current version of the Adafruit_SPIFlash library.
    Not tested but could probably be modified to function with an SD card.
    For use with an SD card refer to https://github.com/hydronics2/SamdAudio

     - Will not work with Adafruit Feather M4 Express and other boards with the SAMD51 processor

    Read this great description in the Adafruit tutorial for getting the WAV files onto your Adafruit M0 Express board
    https://learn.adafruit.com/introducing-itsy-bitsy-m0?view=all#using-spi-flash
    Thanks to Tondy Dicola and Adafruit for making this so easy!

*/

#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>
#include <Audio_FeatherM0.h>

/************************ SPIFlash Instantiations *************************/

// On-board external flash (QSPI or SPI) macros should already
// defined in your board variant if supported
// - EXTERNAL_FLASH_USE_QSPI
// - EXTERNAL_FLASH_USE_CS/EXTERNAL_FLASH_USE_SPI
#if defined(EXTERNAL_FLASH_USE_QSPI)
  Adafruit_FlashTransport_QSPI flashTransport;

#elif defined(EXTERNAL_FLASH_USE_SPI)
  Adafruit_FlashTransport_SPI flashTransport(EXTERNAL_FLASH_USE_CS, EXTERNAL_FLASH_USE_SPI);

#else
  #warning No QSPI/SPI flash are defined on your board variant.h !
	#warning Attempting to use off-board flash !

	#define OFF_BOARD_FLASH_USE_CS 0 // Enter chose CS pin here
	#define OFF_BOARD_FLASH_USE_SPI SPI

	Adafruit_FlashTransport_SPI flashTransport(OFF_BOARD_FLASH_USE_CS,
		OFF_BOARD_FLASH_USE_SPI);

#endif

Adafruit_SPIFlash flash(&flashTransport);

/************************* FatFs Instantiations ***************************/

FatFileSystem fatfs; // File system object from SD fat

/****************************** Audio Player ******************************/
SamdAudio AudioPlayer;

#define NUM_AUDIO_CHANNELS 4 //could be 1,2 or 4 for sound

#define AUDIO_BUFFER_SIZE 1024 //512 works fine for 22.05kh, use 1024 for 32khz and 44.1khz

//indicate sample rate here (use audacity to convert your wav)
const unsigned int sampleRate = 88200; //hz

//your wav file
const char *filename = "test.wav";

void setup()
{
  delay(10);
  Serial.begin(115200);
  while (!Serial); // open the serial to start!

 // Initialize flash library and check its chip ID.
  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1);
  }
  Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin(&flash)) {
    Serial.println("Failed to mount filesystem!");
    Serial.println("Was CircuitPython loaded on the board first to create the filesystem?");
    while(1);
  }
  Serial.println("Mounted filesystem!");

  Serial.print("Initializing Audio Player...");
  if (AudioPlayer.begin(sampleRate, NUM_AUDIO_CHANNELS, AUDIO_BUFFER_SIZE) == -1)
  {
    Serial.println(" failed!");
    return;
  }
  Serial.println(" done.");

}

void loop()
{
	Serial.print("Playing "); Serial.println(filename);
	AudioPlayer.play(filename, 0);

	delay(5000);
}
