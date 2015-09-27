#include "Stack.h"
#include "Enums.h"

//---CONSTANTS---
#define MAX_SIZE 10

//---PROCESSOR---
class CPU_t
{
    private:
    //---REGISTERS---
    int ax;
    int dx;
    Stack_t returns;
    //---STACK_&_CMDS---
    Stack_t Stack;
    int cmds [CMD_NUMBERS];
    int current;
    int lastx, lasty;
    //---SUDDEN_EXIT---
    bool interrupt;

    public:
    int gx;
    int gy;
    double zoomx;
    double zoomy;
    int k;

    CPU_t ();

    //Drawing
    void DrawPoint (double x, double y);

    //Processor Functions
    bool PopAx ();
    bool PopDx ();

    bool Je  (int to);
    bool Jne (int to);
    bool Ja  (int to);
    bool Jae (int to);
    bool Jb  (int to);
    bool Jbe (int to);

    bool Jmp (int to);
    bool Call (int to);
    bool Ret ();

    void Load (FILE* file);
    double Run (int ax_);

    //Other Methods
    void CheckThisOut ();
    bool GetInterrupt ();
    bool OK ();
    bool Exit ();
};

//---CONSTRUCTOR---
CPU_t::CPU_t () :
    ax (0),
    dx (1),
    returns (MAX_SIZE),
    Stack (MAX_SIZE),
    current (0),
    lastx (-9999),
    lasty (-9999),
    interrupt (false),
    gx (400),
    gy (300),
    zoomx   (10),
    zoomy (1)
{
    for (int i = 0; i < CMD_NUMBERS; i ++)
    {
        cmds [i] = 0;
    }
}

//---DRAW_POINT---
void CPU_t::DrawPoint (double x, double y)
{
    //printf ("%lg, %lg;\n", x, y);

    txSetFillColor (RGB (255, 0, 0));
    txSetColor     (RGB (255, 0, 0), 3);

    txCircle (x, y, 2);
}

//---POPAX---
bool CPU_t::PopAx ()
{
	ax = Stack.Pop ();
}
//---POPDX---
bool CPU_t::PopDx ()
{
	dx = Stack.Pop ();
}

//---JMP---
bool CPU_t::Jmp (int to)
{
    current = to - 1;
    return true;
}

//---JE---
bool CPU_t::Je (int to)
{
	if (Stack.Pop() == Stack.Pop()) {current = to; return true;}
	return true;
}
//---JNE---
bool CPU_t::Jne (int to)
{
	if (Stack.Pop() != Stack.Pop()) {current = to; return true;}
	return true;
}
//---JA---
bool CPU_t::Ja (int to)
{
	if (Stack.Pop() > Stack.Pop())  {current = to; return true;}
	return true;
}
//---JAE---
bool CPU_t::Jae (int to)
{
	if (Stack.Pop() >= Stack.Pop()) {current = to; return true;}
	return true;
}
//---JB---
bool CPU_t::Jb (int to)
{
	if (Stack.Pop() < Stack.Pop())  {current = to; return true;}
	return true;
}
//---JBE---
bool CPU_t::Jbe (int to)
{
	if (Stack.Pop() <= Stack.Pop()) {current = to; return true;}
	return true;
}

//---CALL---
bool CPU_t::Call (int to)
{
    returns.Push (current + 1);
    Jmp (to);
    return true;
}

//---RET---
bool CPU_t::Ret ()
{
    Jmp (returns.Pop ());
    return true;
}

//---LOAD---
void CPU_t::Load (FILE* file)
{
    for (int i = 0; i < CMD_NUMBERS; i ++)
    {
        fscanf (file, "%d", & cmds [i]);
    }
}

void CPU_t::CheckThisOut ()
{
    for (int i = 0; i < CMD_NUMBERS; i ++)
    {
        printf ("%d %d;\n", i, cmds[i]);
    }
    printf ("\n\n");
}

//---RUN---
double CPU_t::Run (int ax_)
{
    //---CHECK_OK---
    if (OK () == false) interrupt = true;

    else //---RUN---
    {
    	ax = ax_;

        current = 0;
        while (true)
        {
            //---CHECK_FOR_JUMPING---
                //---JE---
            if (cmds [current] == CMD_JE)
            {
                //printf ("> je started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Je (cmds [current]);
            }
                //---JE---
            if (cmds [current] == CMD_JNE)
            {
                //printf ("> je started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Jne (cmds [current]);
            }
                //---JA---
            if (cmds [current] == CMD_JA)
            {
                //printf ("> je started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Ja (cmds [current]);
            }
                //---JAE---
            if (cmds [current] == CMD_JAE)
            {
                //printf ("> je started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Jae (cmds [current]);
            }
                //---JB---
            if (cmds [current] == CMD_JB)
            {
                //printf ("> je started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Jb (cmds [current]);
            }
                //---JBE---
            if (cmds [current] == CMD_JBE)
            {
                //printf ("> je started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Jbe (cmds [current]);
            }
                //---JMP---
            else if (cmds [current] == CMD_JMP)
            {
                //printf ("> jmp started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Jmp (cmds [current]);
            }
                //---CALL---
            else if (cmds [current] == CMD_CALL)
            {
                //printf ("> jmp started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                current ++;
                Call (cmds [current]);
            }
                //---RET---
            else if (cmds [current] == CMD_RET)
            {
                //printf ("> jmp started;\n> current is %d;\n", current);
                //printf ("> next number is %d;\n\n", cmds[current + 1]);
                Ret ();
            }
            //---OTHER---
                //---PUSHAX---
            else if (cmds [current] == CMD_PUSHAX)
            {
                //printf ("> push ax started;\n> current is %d;\n\n", current);
                Stack.Push (ax);
            }
                //---PUSHDX---
            else if (cmds [current] == CMD_PUSHDX)
            {
                //printf ("> push ax started;\n> current is %d;\n\n", current);
                printf ("dx is %d;\n", dx);
                Stack.Push (dx);
            }
                //---PUSH---
            else if (cmds [current] == CMD_PUSH)
            {
                //printf ("> push started;\n> current is %d;\n\n", current);
                current ++;
                Stack.Push (cmds [current]);
            }
                //---POPAX---
            else if (cmds [current] == CMD_POPAX)
            {
                //printf ("> pop ax started;\n> current is %d;\n\n", current);
                PopAx ();
            }
                //---POPDX---
            else if (cmds [current] == CMD_POPDX)
            {
                //printf ("> pop ax started;\n> current is %d;\n\n", current);
                PopDx ();
            }
                //---POP---
            else if (cmds [current] == CMD_POP)
            {
                //printf ("> pop started;\n> current is %d;\n\n", current);
            }
                //---DUMP---
            else if (cmds [current] == CMD_DUMP)
            {
                //printf ("> dump started;\n> current is %d;\n\n", current);
                Stack.Dump ();
            }
                //---ADD---
            else if (cmds [current] == CMD_ADD)
            {
                //printf ("> add started;\n> current is %d;\n\n", current);
                Stack.Add ();
            }
                //---DRAW---
            else if (cmds [current] == CMD_DRAW)
            {
                //printf ("> Drawing;\n");
                DrawPoint (Stack.Pop(), Stack.Pop());
            }
                //---SUB---
            else if (cmds [current] == CMD_SUB)
            {
                //printf ("> sub started;\n> current is %d;\n\n", current);
                Stack.Sub ();
            }
                //---MUL---
            else if (cmds [current] == CMD_MUL)
            {
                //printf ("> mul started;\n> current is %d;\n\n", current);
                Stack.Mul ();
            }
                //---DIV---
            else if (cmds [current] == CMD_DIV)
            {
                //printf ("> div started;\n> current is %d;\n\n", current);
                Stack.Div ();
            }
                //---SIN---
            else if (cmds [current] == CMD_SIN)
            {
                //printf ("> sin started;\n> current is %d;\n\n", current);
                Stack.Sin ();
            }
                //---COS---
            else if (cmds [current] == CMD_COS)
            {
                //printf ("> cos started;\n> current is %d;\n\n", current);
                Stack.Cos ();
            }
                //---SQRT---
            else if (cmds [current] == CMD_SQRT)
            {
                //printf ("> sqrt started;\n> current is %d;\n\n", current);
                Stack.Sqrt ();
            }
                //---END---
            else if (cmds [current] == CMD_END)
            {
                //printf ("> ended;\n> current is %d;\n\n", current);
                break;
            }

            current ++;
        }
    }
    return dx;
}

//---OK---
bool CPU_t::OK()
{
    if (Stack.OK() == false) { printf ("> Stack > OK returned false;\n\n"); return false;}
    return true;
}

bool CPU_t::Exit ()
{
    if (interrupt == true)
    {
        Stack.Dump ();
        for (int i = 0; i < Stack.GetLength (); i ++)
        {
            Stack.Pop ();
        }
        printf ("> Stack cracked;\n\n");
        return true;
    }

    return false;
}

//---INTERRUPT---
bool CPU_t::GetInterrupt ()
{
    return interrupt;
}

//---END---
