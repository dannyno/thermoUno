/*
 * (c) 2016 Dannyno
 * 
 * Implements a thermometer funtion for arduino UNO
 * 
 * Version history:
 * 2016-02-15 (dannyno): Created
 * 2016-02-15 (dannyno): Create some interaction with the serial console
 * 2016-02-15 (dannyno): Include TMI library
 */

/*******************************************************************************
 *                                                                             *
 * Included libraries                                                          *
 *                                                                             *
 *******************************************************************************/

/*
 * This library can be downloaded from https://github.com/dannyno/TMI
 * For information on installing libraries, see: http://www.arduino.cc/en/Guide/Libraries 
 */
#include <TMI_types.h>
#include <TMI.h>

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

/* Test table */
enum TableIndices
{
    TOP_MENU,
    SUB_MENU_1,
    SUB_MENU_1_1,
    SUB_MENU_1_1_1,
    SUB_MENU_1_1_2,
    SUB_MENU_1_1_3,

    SUB_MENU_1_2,
    
    SUB_MENU_2,
    SUB_MENU_2_1,
    SUB_MENU_2_2,
    
    TABLE_LENGTH
};

/* Local prototypes */
int dummyAction(void);

static const TMI_item test_cli_struct[] = {
    /*{INDEX, DESCRIPTION_TEXT, PARENT, BELOW, THROUGH, action}*/
    {TOP_MENU, "Top menu, where do you want to go?", NO_PARENT, NO_BELOW, SUB_MENU_1, NULL},
        {SUB_MENU_1, "Sub menu 1", TOP_MENU, SUB_MENU_2, SUB_MENU_1_1, NULL},
            {SUB_MENU_1_1, "Sub menu 1-1", SUB_MENU_1, SUB_MENU_1_2, SUB_MENU_1_1_1, NULL},
                {SUB_MENU_1_1_1, "Sub menu 1-1-1", SUB_MENU_1_1, SUB_MENU_1_1_2, NO_ELDER, &dummyAction},
                {SUB_MENU_1_1_2, "Sub menu 1-1-2", SUB_MENU_1_1, SUB_MENU_1_1_3, NO_ELDER, &dummyAction},
                {SUB_MENU_1_1_3, "Sub menu 1-1-3", SUB_MENU_1_1, NO_BELOW, NO_ELDER, &dummyAction},
            {SUB_MENU_1_2, "Sub menu 1-2", SUB_MENU_1, NO_BELOW, NO_ELDER, &dummyAction},
        {SUB_MENU_2, "Sub menu 2", TOP_MENU, NO_BELOW, SUB_MENU_2_1, NULL},
            {SUB_MENU_2_1, "Sub menu 2-1", SUB_MENU_2, SUB_MENU_2_2, NO_ELDER, &dummyAction},
            {SUB_MENU_2_2, "Sub menu 2-2", SUB_MENU_2, NO_BELOW, NO_ELDER, &dummyAction},
    {TABLE_LENGTH, "", NO_PARENT, NO_BELOW, NO_ELDER, NULL}
};

/*******************************************************************************
 *                                                                             *
 * Functions                                                                   *
 *                                                                             *
 *******************************************************************************/

// Function to print the menu from current item:
void printMenu(const TMI_item * pTable, unsigned int index)
{
    unsigned int currentIndex = index;
    unsigned int num = 1;
    Serial.println("0: go up -1: exit");
    Serial.println(pTable[currentIndex].text);
    currentIndex = pTable[currentIndex].elder;
    if (currentIndex != 0)
    {
      Serial.print("\t");
      Serial.print(num);
      Serial.print(".");
      num++;
      Serial.println(pTable[currentIndex].text);
      while (pTable[currentIndex].below != NO_BELOW)
      {
          currentIndex = pTable[currentIndex].below;
          Serial.print("\t");
          Serial.print(num);
          Serial.println(".");
          num++;
          Serial.println(pTable[currentIndex].text);
      }
    }
}

/* dummy action function */
int dummyAction(void)
{
  Serial.println("Dummy action");
  return 0;
}

/* Not super good but that works for test */
int myPrintFunction(const char * toPrint)
{
  Serial.print(toPrint);
  return 0;
}

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
  int myInt = 0;
  int numRead = 0;
  unsigned int currentIndex = 0;
  unsigned int errCode = TMI_init(&test_cli_struct[0], TABLE_LENGTH);
  
  Serial.print("Error Code: ");
  Serial.print(errCode);
  Serial.println(' ');
  Serial.println("Whole table:");
  TMI_display_table(&myPrintFunction);
  while (myInt != -1)
  {
    printMenu(&test_cli_struct[0], currentIndex);
    numRead = readDataFromSerial(&myInt);
    if (numRead > 0)
    {
      currentIndex = TMI_item_process(myInt);
    }
  }
  
}
