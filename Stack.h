//---CONSTANTS---
#include <math.h>

#define MAX_SIZE 100
#define CMD_NUMBERS 100
#define ZERO_ 1e-9
#define EXCEPTION_ -100001

//---MY_STACK---
class Stack_t
{
    private:
    double* arr_;
    int current_;
    int length_;

    public:

    Stack_t ();
    Stack_t (const Stack_t&);
    Stack_t (int length);
   ~Stack_t ();

    Stack_t& operator= (const Stack_t&);

    bool Push (double a);
    double  Pop  ();

    bool  Add ();
    bool  Sub ();
    bool  Mul ();
    bool  Div ();
    bool  Sin ();
    bool  Cos ();
    bool Sqrt ();

    int GetLength ();

    bool OK ();
    bool Dump ();
};

//---CONSTRUCTORS---
Stack_t::Stack_t ():
    arr_ (new double [MAX_SIZE]),
    current_ (0),
    length_ (MAX_SIZE)
{
	for(int i = 0; i < length_; i ++) arr_ [i] = 0;
}

Stack_t::Stack_t (const Stack_t& st):
    arr_ (new double [st.length_]),
    current_ (st.current_),
    length_  ( st.length_)
{
    for (int i = 0; i < length_; i ++)
    {
        arr_ [i] = st.arr_ [i];
    }
}

Stack_t::Stack_t (int length) :
    arr_   (new double [length]),
    current_ (0),
    length_ (length)
{
    for (int i = 0; i < length_; i ++)
    {
        arr_ [i] = 0;
    }
}

Stack_t::~Stack_t ()
{
    delete [] arr_;
}

Stack_t& Stack_t::operator= (const Stack_t& st)
{
    current_    = st.current_;
    length_     =  st.length_;

    delete [] arr_;
    arr_ = new double [length_];
    for (int i = 0; i < length_; i ++)
    {
        arr_ [i] = st.arr_ [i];
    }

    return *this;
}

//---METHODS---
//>---PUSH---
bool Stack_t::Push (double a)
{
    if (current_ >= length_)
    {
        printf ("> EXCEPTION caught while\t_PUSH_\twas running;\n");
        printf ("> > Stack is Full;\n\n");

        return false;
    }
    arr_ [current_] = a;
    current_ ++;

    return true;
}

//>---POP---
double Stack_t::Pop ()
{
    if (current_ <= 0)
    {
        printf ("> EXCEPTION caught while\t_POP_\twas running;\n");
        printf ("> > There are no elements in Stack;\n\n");

        return EXCEPTION_;
    }

    current_ --;
    double result = arr_ [current_];
    arr_ [current_] = 0;

    return result;
}

//>---MATH---
bool Stack_t::Add ()
{
    double p1 = Pop ();
    double p2 = Pop ();

    if (fabs(p1 - EXCEPTION_) < ZERO_ || fabs(p2 - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_ADD_\twas running;\n\n");
        return false;
    }

    Push (p1 + p2);

    return true;
}

bool Stack_t::Sub ()
{
    double p1 = Pop ();
    double p2 = Pop ();

    if (fabs(p1 - EXCEPTION_) < ZERO_ || fabs(p2 - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_SUB_\twas running;\n\n");
        return false;
    }

    Push (p1 - p2);

    return true;
}

bool Stack_t::Mul ()
{
    double p1 = Pop ();
    double p2 = Pop ();

    if (fabs(p1 - EXCEPTION_) < ZERO_ || fabs(p2 - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_MUL_\twas running;\n\n");
        return false;
    }

    Push (p1 * p2);

    return true;
}

bool Stack_t::Div ()
{
    double p1 = Pop ();
    double p2 = Pop ();

    if (fabs(p1 - EXCEPTION_) < ZERO_ || fabs(p2 - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_DIV_\twas running;\n\n");
        return false;
    }

    if (fabs(p1) > ZERO_) Push (p1 / p2);
    else Push (0);

    return true;
}

bool Stack_t::Sin ()
{
    double p = Pop ();

    if (fabs(p - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_SIN_\twas running;\n\n");
        return false;
    }

    Push (sin (p/10));

    return true;
}

bool Stack_t::Cos ()
{
    double p = Pop ();

    if (fabs(p - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_COS_\twas running;\n\n");
        return false;
    }

    Push (cos (p/10));

    return true;
}

bool Stack_t::Sqrt ()
{
    double p = Pop ();

    if (fabs(p - EXCEPTION_) < ZERO_)
    {
        printf ("> EXCEPTION caught while\t_SQRT_\twas running;\n\n");
        return false;
    }

    Push (sqrt (p));

    return true;
}

//>---AWESOMNESS---
int Stack_t::GetLength ()
{
    return length_;
}

bool Stack_t::OK ()
{
    if (arr_ == 0 || length_ <= 0) return false;
    return true;
}

bool Stack_t::Dump ()
{
    printf ("> DUMP function called;\n");

    printf ("> > Length:\t%d;\n", length_);
    printf ("> > Current:\t%d;\n", current_);
    printf ("> > Elements:\n");

    for (int i = 0; i < length_; i ++)
    {
        if (i == current_) printf ("> > > %d. \t%lg; - current\n", i, arr_ [i]);
        else               printf ("> > > %d. \t%lg;\n", i, arr_ [i]);
    }

    printf ("> DUMP finished;\n\n");
    //What for do i need it ?!
    /*printf ("Elements out of stack :\n");

    for (int i = length_; i < MAX_SIZE; i ++)
    {
        printf ("%d. %lg;\n", i + 1, arr_ [i]);
    }*/

    return true;
}

