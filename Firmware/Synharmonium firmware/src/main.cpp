#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 7; //seven rows
const byte COLS = 13; //thirteen columns
String bassKeys[ROWS][COLS] = {
    {"Db3","Ab3","Eb3","Bb3","Fn3","Cn3","Gn3","Dn3","An3","En3","Bn3","Fs3","+8va"},                             // thirds, up octave
    {"Dbr","Abr","Ebr","Bbr","Fnr","Cnr","Gnr","Dnr","Anr","Enr","Bnr","Fsr","-8va"},                             // roots, down octave
    {"Dbmaj","Abmaj","Ebmaj","Bbmaj","Fnmaj","Cnmaj","Gnmaj","Dnmaj","Anmaj","Enmaj","Bnmaj","Fsmaj","+1/2"},     // major chords, up half step
    {"Dbmin","Abmin","Ebmin","Bbmin","Fnmin","Cnmin","Gnmin","Dnmin","Anmin","Enmin","Bnmin","Fsmin","-1/2"},     // minor chords, down half step
    {"Db7th","Ab7th","Eb7th","Bb7th","Fn7th","Cn7th","Gn7th","Dn7th","An7th","En7th","Bn7th","Fs7th","maj/dom"},  // 7th chords, major 7th vs dominant 7th toggle
    {"Dbdim","Abdim","Ebdim","Bbdim","Fndim","Cndim","Gndim","Dndim","Andim","Endim","Bndim","Fsdim","dim/aug"},  // diminished or augmented chords, toggle between the two
    {"fu0","fu1","fu2","fu3","fu4","fu5","fu6","fu7","fu8","fu9","fu10","fu11","fu12"}  
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
    
    #define row0  32
    #define row1  31
    #define row2  30
    #define row3  29
    #define row4  28
    #define row5  27
    #define row6  26

    #define col0  45
    #define col1  44
    #define col2  43
    #define col3  42
    #define col4  41
    #define col5  40
    #define col6  39
    #define col7  38
    #define col8  37
    #define col9  36
    #define col10 35
    #define col11 34
    #define col12 33



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