#include "TXLib.h"
#include "CPU.h"

#define PRESSED GetAsyncKeyState

//---MAIN---
int main ()
{
    CPU_t cpu;

    FILE* cmd = fopen ("cmd.txt", "r");
    cpu.Load (cmd);
    fclose (cmd);

    double vzx = .2, vzy = .03;

    txCreateWindow (800, 600);

    return 1;
    //---LOOP---
    txBegin ();
    while (!PRESSED (VK_ESCAPE))
    {
        txSetFillColor (TX_BLACK);
        txClear ();

        //---LINES---
        txSetFillColor (RGB (255, 0, 0));
        txSetColor     (RGB (255, 0, 0));

        txSetColor (TX_WHITE, 2);
        txLine (400, 0, 400, 600);
        txLine (0, 300, 800, 300);

        //---RUN---
        cpu.Run (1);

        //---SCALE---
        if (PRESSED (VK_RIGHT)) cpu.zoomx += vzx;
        if (PRESSED  (VK_LEFT)) cpu.zoomx -= vzx;
        if (PRESSED    (VK_UP)) cpu.zoomy -= vzy;
        if (PRESSED  (VK_DOWN)) cpu.zoomy += vzy;

        if (PRESSED  (VK_SPACE)) cpu.zoomy = 0;

        //---INTERRUPT---
        if (cpu.GetInterrupt () == true) break;

        txSleep (1);
    }
    txEnd ();


    return 0;
}
