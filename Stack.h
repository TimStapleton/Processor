//---CONSTANTS---
#define MAX_SIZE 10
#define CMD_NUMBERS 100
#define zero 1e-6

//---MY_STACK---
class Stack_t
{
    private:
    double* arr_;
    int current_;
    int length_;
    int size_;

    public:

    Stack_t ();
    Stack_t (const Stack_t&);
    Stack_t (int size);
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
    arr_ (new double [1]),
    current_ (0),
    length_ (1),
    size_ (2)
{
	arr_ [0] = 0;
}

Stack_t::Stack_t (const Stack_t& st):
    arr_ (new double [st.length_]),
    current_ (st.current_),
    length_  ( st.length_),
    size_    (   st.size_)
{
    arr_ = new double [length_];
    for (int i = 0; i < length_; i ++)
    {
        arr_ [i] = st.arr_ [i];
    }
}

Stack_t::Stack_t (int size) :
    arr_   (new double [size]),
    current_ (0),
    length_ (size),
    size_ (size)
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
    size_       =    st.size_;

    delete [] arr_;
    arr_ = new double [length_];
    for (int i = 0; i < length_; i ++)
    {
        arr_ [i] = st.arr_ [i];
    }

    return *this;
}

//---METHODS---
//>---PUSH/POP---
bool Stack_t::Push (double a)
{
    arr_ [current_] = a;
    current_ ++;

    return true;
}

double Stack_t::Pop ()
{
    if (current_ < 0) return 0;

    current_ --;
    double result = arr_ [current_];
    return result;
}

//>---MATH---
bool Stack_t::Add ()
{
    double a1 = Pop ();
    double a2 = Pop ();
    Push (a1 + a2);

    return true;
}

bool Stack_t::Sub ()
{
    double a1 = Pop ();
    double a2 = Pop ();
    Push (a1 - a2);

    return true;
}

bool Stack_t::Mul ()
{
    double a1 = Pop ();
    double a2 = Pop ();
    Push (a1 * a2);

    return true;
}

bool Stack_t::Div ()
{
    double a1 = Pop ();
    double a2 = Pop ();
    if (fabs(a1) > zero) Push (a1 / a2);
    else Push (0);

    return true;
}

bool Stack_t::Sin ()
{
    Push (sin (Pop ()/10));

    return true;
}

bool Stack_t::Cos ()
{
    Push (cos (Pop ()/10));

    return true;
}

bool Stack_t::Sqrt ()
{
    Push (sqrt (Pop ()));

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
    printf ("Hello, my name is @stack.\n");
    txSleep (200);
    printf ("I am fifteen-year old stack with lot of experience. :)\n\n");
    txSleep (600);

    printf ("My length is %d;\n", length_);
    printf ("my elements :\n");

    for (int i = 0; i < length_; i ++)
    {
        printf ("%d. %lg;\n", i, arr_ [i]);
    }

    txSleep (200);
    printf ("Elements out of stack :\n");

    for (int i = length_; i < MAX_SIZE; i ++)
    {
        printf ("%d. %lg;\n", i + 1, arr_ [i]);
    }

    return true;
}

