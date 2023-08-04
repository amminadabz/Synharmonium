#include<Arduino.h>

// ================= INCLUDES ==================
#include <Code_Sc.h>
#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>

// ============ SPEED CONFIGURATION ============
ScanDelay scanDelay(9000);

// ================== SCANNER ==================
uint8_t readPins[] = {45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33};  // columns
uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

Scanner_uC scanner(LOW, readPins, readPinCount);    // Cathode --> rows. Check High/low later if shit dont work

// =================== CODES ===================
Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);

// =================== ROWS ====================
Key* ptrsKeys_0[] = { &s_1, &s_2 };
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);
Row row_0(scanner, 0, ptrsKeys_0, keyCount_0);

Key* ptrsKeys_1[] = { &s_a, &s_b };
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
Row row_1(scanner, 1, ptrsKeys_1, keyCount_1);

// ################### MAIN ####################
void setup()
{
}

void loop()
{
    row_0.process();
    row_1.process();
    scanDelay.delay();
}
