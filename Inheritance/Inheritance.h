class Mammal
{
    public:
        Mammal();
        Mammal(char* name);
        virtual void eat();
        char* getName();
        virtual ~Mammal();
    protected:
        char* name;
        static int count;
};
// this is how we do this
int Mammal::count = 0;

class Dog: public Mammal
{
    public:
        Dog();
        Dog(char* name);
        void eat();
        virtual ~Dog();
};

class Cat: public Mammal
{
    public:
        Cat();
        Cat::Cat();
        void eat();
        virtual ~Cat();

};