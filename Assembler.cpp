#include "TXLib.h"
#include "Enums.h"

#define CMD_NUMBERS 200

//---PROTOTYPES---
int Translate (char str[]);
bool Compile (FILE* file, int mass[], int labels[]);

//---FUNCTIONS---
int Translate (char str[])
{
        if (stricmp (str,  "push") == 0) return  CMD_PUSH;
        if (stricmp (str, "popax") == 0) return CMD_POPAX;
        if (stricmp (str, "popdx") == 0) return CMD_POPDX;
   else if (stricmp (str,   "pop") == 0) return   CMD_POP;
        if (stricmp (str,    "je") == 0) return    CMD_JE;
        if (stricmp (str,   "jne") == 0) return   CMD_JNE;
        if (stricmp (str,    "ja") == 0) return    CMD_JA;
        if (stricmp (str,   "jae") == 0) return   CMD_JAE;
        if (stricmp (str,    "jb") == 0) return    CMD_JB;
        if (stricmp (str,   "jbe") == 0) return   CMD_JBE;
        if (stricmp (str,   "jmp") == 0) return   CMD_JMP;
        if (stricmp (str,   "ret") == 0) return   CMD_RET;
        if (stricmp (str,  "call") == 0) return  CMD_CALL;
        if (stricmp (str,  "dump") == 0) return  CMD_DUMP;
        if (stricmp (str,   "add") == 0) return   CMD_ADD;
        if (stricmp (str,   "sub") == 0) return   CMD_SUB;
        if (stricmp (str,   "mul") == 0) return   CMD_MUL;
        if (stricmp (str,   "div") == 0) return   CMD_DIV;
        if (stricmp (str,   "sin") == 0) return   CMD_SIN;
        if (stricmp (str,   "cos") == 0) return   CMD_COS;
        if (stricmp (str,  "sqrt") == 0) return  CMD_SQRT;
        if (stricmp (str,  "draw") == 0) return  CMD_DRAW;
        if (stricmp (str,   "end") == 0) return   CMD_END;
        return -1;
}

bool Compile (FILE* file, int mass[], int labels[])
{
    printf ("Compiling\n");

    assert (file);
    assert (mass);
    assert (labels);

    int cur = 0;
    char str[8] = "";
    //String_t my_str (str);

    while (true)
    {
        if (fscanf (file, "%s", str) == EOF) {printf ("SUDDENLY: the file was read !\n\n"); return false;}
        //assert (str);

        int n = Translate (str);

        //---CHECK_FOR_LABEL---
        if (str[0] == ':')
        {
            int lcur = str[1] - '0';
            printf ("lcur is %d \n cur is %d; \n", lcur, cur);
            labels [lcur] = cur;
            cur --;
        }
        //---CHECK_FOR_PUSH---
        else if (n == CMD_PUSH)
        {
            int  in = 0;
            bool haveNum = (fscanf (file, "%d", &in) == 1);

            if (haveNum)
            {
                mass [cur] = CMD_PUSH;
                cur ++;
                mass [cur] = in;
            }
            else
            {
				char option [3] = "";
                fscanf  (file, "%s", &option);
                if (strcmp(option, "ax") == 0)mass [cur] = CMD_PUSHAX;
		        else mass [cur] = CMD_PUSHDX;
            }
        }
        //---CHECK_FOR_JE---
        else if (n == CMD_JE)
        {
            int in = 0;
            fscanf (file, "%d", &in);
            //printf ("%d\n\n\n\n\n", in);

            mass [cur] = CMD_JE;
            cur ++;
            mass [cur] = labels[in];
        }
        //---CHECK_FOR_JNE---
        else if (n == CMD_JNE)
        {
            int in = 0;
            fscanf (file, "%d", &in);
            //printf ("%d\n\n\n\n\n", in);

            mass [cur] = CMD_JNE;
            cur ++;
            mass [cur] = labels[in];
        }
        //---CHECK_FOR_JA---
        else if (n == CMD_JA)
        {
            int in = 0;
            fscanf (file, "%d", &in);
            //printf ("%d\n\n\n\n\n", in);

            mass [cur] = CMD_JA;
            cur ++;
            mass [cur] = labels[in];
        }
        //---CHECK_FOR_JAE---
        else if (n == CMD_JAE)
        {
            int in = 0;
            fscanf (file, "%d", &in);
            //printf ("%d\n\n\n\n\n", in);

            mass [cur] = CMD_JAE;
            cur ++;
            mass [cur] = labels[in];
        }
        //---CHECK_FOR_JB---
        else if (n == CMD_JB)
        {
            int in = 0;
            fscanf (file, "%d", &in);
            //printf ("%d\n\n\n\n\n", in);

            mass [cur] = CMD_JB;
            cur ++;
            mass [cur] = labels[in];
        }
        //---CHECK_FOR_JBE---
        else if (n == CMD_JBE)
        {
            int in = 0;
            fscanf (file, "%d", &in);
            //printf ("%d\n\n\n\n\n", in);

            mass [cur] = CMD_JBE;
            cur ++;
            mass [cur] = labels[in];
        }
        //---CHECK_FOR_JMP---
        else if (n == CMD_JMP)
        {
            int in = 0;
            fscanf (file, "%d", &in);

            mass [cur] = CMD_JMP;
            cur ++;
            mass [cur] = labels [in];
        }
        //---CHECK_FOR_CALL---
        else if (n == CMD_CALL)
        {
            int in = 0;
            fscanf (file, "%d", &in);

            mass [cur] = CMD_CALL;
            cur ++;
            mass [cur] = labels [in];
        }
        else mass [cur] = n;

        printf ("cur is \t%d\n", cur);
        assert (cur >= 0 && cur <= CMD_NUMBERS);

        if (n == CMD_END || cur >= CMD_NUMBERS) {printf ("Compiled\n\n"); return true;}
        cur ++;
    }
    return true;
}

//---MAIN---
int main ()
{
    FILE* input = fopen ("input.txt", "r");
    FILE*   cmd = fopen   ("cmd.txt", "w");

    int commands [CMD_NUMBERS] = {};
    int labels [CMD_NUMBERS] = {};

    //---Problem-Here---
    bool firstcompilation  = Compile (input, commands, labels);
    for (int i = 0; i < 50; i ++)
    {
        printf ("Mass[%d] is %d;\n", i, commands[i]);
    }

    rewind (input);
    bool secondcompilation = Compile (input, commands, labels);
    //---End-Of-Problem---

    printf ("%d %d\n\n", (int)firstcompilation, (int)secondcompilation);

    for (int i = 0; i < 50; i ++)
    {
        printf ("Mass[%d] is %d;\n", i, commands[i]);
    }

    for (int i = 0; i < CMD_NUMBERS; i ++)
    {
        if (commands [i] == CMD_PUSH)
        {
            fprintf (cmd, "%d\n", commands [i]);
            i ++;
            fprintf (cmd, "%d\n", commands [i]);
        }
        else if (commands [i] == CMD_JE || commands [i] == CMD_JMP)
        {
            printf ("JE or JMP detected;\n commands[i]  is %d; commands [i + 1] is %d; labels [commands [i + 1]] is %d;\n\n", commands [i], commands [i + 1], labels[commands [i + 1]]);

            fprintf (cmd, "%d\n", commands [i]);
            i ++;
            fprintf (cmd, "%d\n", commands [i]);
        }
        else fprintf (cmd, "%d\n", commands [i]);
        if (commands [i] == CMD_END && commands [i + 1] == CMD_END) break;
    }

    fclose (input);
    fclose (cmd);

    return 0;
}
