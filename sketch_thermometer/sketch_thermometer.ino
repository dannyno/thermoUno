/*
 * (c) 2016 Dannyno
 * 
 * Implements a thermometer funtion for arduino UNO
 * 
 * Version history:
 * 2016-02-15 (dannyno): Created
 * 2016-02-15 (dannyno): Create some interaction with the serial console
 */

/*******************************************************************************
 *                                                                             *
 * Static definitions                                                          *
 *                                                                             *
 *******************************************************************************/
#define WELCOME_STRING "-- ThermoUNO welcome --"
typedef enum{
  BAUD_300 = 300L,
  BAUD_600 = 600L,
  BAUD_1200 = 1200L,
  BAUD_2400 = 2400L,
  BAUD_4800 = 4800L,
  BAUD_9600 = 9600L,
  BAUD_14400 = 14400L,
  BAUD_19200 = 19200L,
  BAUD_28800 = 28800L,
  BAUD_31250 = 31250L,
  BAUD_38400 = 38400L,
  BAUD_57600 = 57600L,
  BAUD_115200 = 115200L
} baudSpeed_t;

/*******************************************************************************
 *                                                                             *
 * Functions                                                                   *
 *                                                                             *
 *******************************************************************************/

/*
 * This function is called when initialization is done
 */
void initDone()
{
  Serial.println(WELCOME_STRING);
}

/*
 * This function initializes the serial port to 8-N-1, i.e. 8 data bits, no 
 * parity bits, one stop bit.
 * 
 * Inputs:
 *   - baud: the baud speed. Valid values are: 300, 600, 1200, 2400, 4800, 9600, 
 *           14400, 19200, 28800, 31250, 38400, 57600, and 115200.
 */
void serialInit(baudSpeed_t speed)
{
  Serial.begin(speed, SERIAL_8N1);
  while(!Serial){
    ; // Wait for serial port to connect
  }
}

/*******************************************************************************
 *                                                                             *
 * Init function                                                               *
 *                                                                             *
 *******************************************************************************/
void setup() 
{
  // init serial port to 9600 baud 
  serialInit(BAUD_115200);
  
  // Init done
  initDone();

}

/*******************************************************************************
 *                                                                             *
 * Loop function                                                               *
 *                                                                             *
 *******************************************************************************/
void loop() 
{
  int in_byte;

  if (Serial.available() > 0)
  {
    in_byte = Serial.read();

    Serial.write(in_byte);
  }
  

  
}
