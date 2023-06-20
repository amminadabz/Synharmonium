#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 7; //seven rows
const byte COLS = 13; //thirteen columns
char bassKeys[ROWS][COLS] = {
    // there need to be more unique values here than i can type, so we're just using an array of 
    // hexes which fits into ascii space. the characters they represent don't really matter, and 
    // they will be converted to something usable once out of the keymatrix library.
    {'\x00','\x01','\x02','\x03','\x04','\x05','\x06','\x07','\x08','\x09','\x0A','\x0B','\x0C'},  // thirds, up octave
    {'\x10','\x11','\x12','\x13','\x14','\x15','\x16','\x17','\x18','\x19','\x1A','\x1B','\x1C'},  // roots, down octave
    {'\x20','\x21','\x22','\x23','\x24','\x25','\x26','\x27','\x28','\x29','\x2A','\x2B','\x2C'},  // major chords, up half step
    {'\x30','\x31','\x32','\x33','\x34','\x35','\x36','\x37','\x38','\x39','\x3A','\x3B','\x3C'},  // minor chords, down half step
    {'\x40','\x41','\x42','\x43','\x44','\x45','\x46','\x47','\x48','\x49','\x4A','\x4B','\x4C'},  // 7th chords, major 7th vs dominant 7th toggle
    {'\x50','\x51','\x52','\x53','\x54','\x55','\x56','\x57','\x58','\x59','\x5A','\x5B','\x5C'},  // diminished or augmented chords, toggle between the two
    {'\x60','\x61','\x62','\x63','\x64','\x65','\x66','\x67','\x68','\x69','\x6A','\x6B','\x6C'}   // function row
};
byte rowPins[ROWS] = {32, 31, 30, 29, 28, 27, 26}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33}; //connect to the column pinouts of the keypad

Keypad bassKeyboard = Keypad( makeKeymap(bassKeys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;

// microcontroller pinout, see /hardware/pinout_r***.ods
  // bass keyboard
    #define d92   22
    #define d93   23
    #define d94   24
    #define d95   25
    
    // #define row0  32
    // #define row1  31
    // #define row2  30
    // #define row3  29
    // #define row4  28
    // #define row5  27
    // #define row6  26

    // #define col0  45
    // #define col1  44
    // #define col2  43
    // #define col3  42
    // #define col4  41
    // #define col5  40
    // #define col6  39
    // #define col7  38
    // #define col8  37
    // #define col9  36
    // #define col10 35
    // #define col11 34
    // #define col12 33



// put function declarations here:


void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}

void loop() {
    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

    // Fills bassKeyboard.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (bassKeyboard.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( bassKeyboard.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (bassKeyboard.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print(bassKeyboard.key[i].kchar);
                Serial.println(msg);
            }
        }
    }
}

// put function definitions here:
