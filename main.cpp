#include "mbed.h"
#include "funkcije.h"

#define MAX_BRZINA 0.8
#define STD_BRZINA 0.4
#define MIN_BRZINA 0.1

int main()
{
    pwm_L.period(0.02);
    pwm_D.period(0.02);

    timer.start();              //debounce
    button.mode(PullUp);        //Postavljanje moda guba za paljenje/gašenje vozila
    button.rise(&toggle);       //Poziva funkciju koja sve pokreće/zaustavlja

    while(true)
    {
        if(aktivan)
        {
            ucitaj_podatke();
            pokreni_motore();
        }
        else {
            pwm_L.write(0);
            pwm_D.write(0);
        }

        thisThread:ThisThread::sleep_for(1);
    }
}

void pokreni_motore()
{
        pwm_L.write(lijevi.brzina);
        pwm_D.write(desni.brzina);
}

void toggle()
{
    if(timer.read() > 0.25)                         //Unutar ove petlje kako bi smo izbjegli debouncing
    {
        aktivan = !aktivan;

        timer.reset();
    }
}

void ucitaj_podatke()
{
    desni.foto = snzr_D.read() * 3300;                  //Max vrijedost na svijetlosti iznosi 3300
    lijevi.foto = snzr_L.read() * 3300;

    if(abs(desni.foto - lijevi.foto) < 350)
    {                                          //Nastavi ravno
        desni.brzina = STD_BRZINA;        
        lijevi.brzina = STD_BRZINA; 

        return;
    }

    if(desni.foto > lijevi.foto)                        //Skreni desno
    {
        lijevi.brzina = STD_BRZINA;                     //Pokrećemo motor sa suprotne strane senzora kako bi smo skrenuli u smijeru senzora
        desni.brzina = MIN_BRZINA;
    }
    else if (lijevi.foto > desni.foto )                 //Skreni lijevo
    {
        desni.brzina = STD_BRZINA;        
        lijevi.brzina = MIN_BRZINA;
    }

}

void error_led()
{
    ledica = !ledica;

    ThisThread::sleep_for(100);
}