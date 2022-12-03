#include"mbed.h"

InterruptIn button(PC_13);      //User gumb na Nucleu

PwmOut pwm_L(D7);               //Pwm za lijevi motor
PwmOut pwm_D(D12);              //Pwm za desni motor

Timer timer;                    //Timer za debounce
Ticker led;                     //Za error led

DigitalOut ledica(LED1);        //Error led
AnalogIn snzr_L(A1);            //Lijevi fotootpornik
AnalogIn snzr_D(A5);            //Desni fotootpornik

bool aktivan = true;

struct motor
{
    float brzina;               //Zadana brzina
    float foto;                 //Vrijedost na fotootporniku
};
motor desni;
motor lijevi;

void toggle();
void pokreni_motore();
void ucitaj_podatke();
void error_led();