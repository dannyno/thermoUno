#include <thermap.h>

/*
 * (c) 2016 Dannyno
 * 
 * Implements a thermometer funtion for arduino UNO
 * 
 * Version history:
 * 2016-02-15 (dannyno): Created
 * 2016-02-15 (dannyno): Create some interaction with the serial console
 * 2016-02-23 (dannyno): Output a temperature
 */

/*******************************************************************************
 *                                                                             *
 * Static definitions                                                          *
 *                                                                             *
 *******************************************************************************/
#define WELCOME_STRING "-- ThermoUNO welcome --"

#define SERIESRESISTOR_OHM      10000
#define THERMISTOR_ANALOG_PIN   A0

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

#define NUM_ENTRIES 21

const thermap_elt_t entries[NUM_ENTRIES] =
{
  {-40,2008000},
  {-30,1032000},
  {-20,551500},
  {-10,306000},
  {0,175500},
  {10,103900},
  {20,63350},
  {25,50000},
  {30,39710},
  {40,25525},
  {50,16795},
  {60,11295},
  {70,7750},
  {80,5420},
  {90,3855},
  {100,2785},
  {110,2040},
  {120,1515},
  {130,1140},
  {140,865},
  {150,665}
};

thermap_table_t table =
{
  entries,
  NUM_ENTRIES
};

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
  Serial.print("Table consistency: ");
  Serial.println(thermap_check_table(&table));

  Serial.print("Number of entries: ");
  unsigned int num = thermap_get_table_length(&table);
  Serial.println(num);

  //outputTableContent();
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

/*
 * This function reads data from the serial port.
 * 
 * Inputs:
 *  - in: input data
 * 
 * return value: number of bytes read
 * 
 */
int readDataFromSerial(int *in)
{
  int returnValue = Serial.available();
  if (returnValue > 0)
  {
    *in = Serial.read();
  }
  return returnValue;
}

/*
 * Outputs data on the serial port
 * 
 * Inputs:
 *  - data: pointer to the data to be ouput
 *          (should be the same as input to readDataFromSerial)
 * 
 * return value: None
 * 
 */
void outputDataOnSerial(int *data)
{
  Serial.write(*data);
}

/*
 * Displays the entire table content
 */
void outputTableContent(void)
{
  unsigned int num = thermap_get_table_length(&table);
  for (int i = 0;i< num;i++)
  {
    Serial.print(table.table[i].temp);
    Serial.print(",");
    Serial.println(table.table[i].R);
  }
}

/*
 * Analog reading on A0
 */
float thermistorRead(void)
{
  float reading = analogRead(THERMISTOR_ANALOG_PIN);
  reading = (1023 / reading) - 1;
  reading = SERIESRESISTOR_OHM / reading;
  return reading;
}

/*******************************************************************************
 *                                                                             *
 * Init function                                                               *
 *                                                                             *
 *******************************************************************************/
void setup() 
{
  // init serial port to 9600 baud 
  serialInit(BAUD_9600);
  
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
  float value = thermistorRead();
  value = ((float)thermap_get_temp((long)value, &table) )/ 100;
  Serial.println(value);

  delay(1000);
  
}
