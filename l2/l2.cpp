#include <iostream>

class Complex
{
    int real;
    int img;

public:
    Complex(int r = 0, int i = 0) : real(r), img(i) {}
    /*
    Complex(int r, int i)
    {
        real = r;
        img = i;
    }
    */
    Complex(Complex const &c)
    {
        real = c.real;
        img = c.img;
    }
    void display()
    {
        std::cout << real << " + " << img << "*i" << std::endl;
    }
    Complex add(Complex c)
    {
        Complex result;
        result.real = real + c.real;
        result.img = img + c.img;
        return result;
    }
    Complex operator+(Complex c)
    {
        // return add(c);
        Complex result;
        result.real = real + c.real;
        result.img = img + c.img;
        return result;
    }
    friend Complex operator+(int a, Complex c);
    
    friend std::istream &operator>>(std::istream &in, Complex &c);

    // Overloaded << operator (for output)
    friend std::ostream &operator<<(std::ostream &out, const Complex &c);
    
};
std::istream &operator>>(std::istream &in, Complex &c) {
    std::cout << "Enter real and imaginary parts: ";
    in >> c.real >> c.img;
    return in;
}

// Overloading << operator for output
std::ostream &operator<<(std::ostream &out, const Complex &c) {
    out << c.real << " + " << c.img << "*i";
    return out;
}
Complex operator+(int a, Complex c)
{
    Complex result;
    result.real = a + c.real;
    result.img = c.img;
    return result;
}
void menu()
{
    int choice = 1;
    Complex array[10];
    while (choice != 0)
    {
        std::cout << "1. Add number\n";
        std::cout << "2. Show numbers\n";
        std::cout << "3. Add 2 numbers\n";
        std::cout << "0. Exit\n";
        std::cin >> choice;
        if (choice == 0)
        {
            return;
        }
        else if (choice == 1)
        {
            Complex C1;
            std::cin >> C1;
            std::cout << "You have added: " << C1;
            array[0] = C1;
        }
        else if (choice == 2)
        {
            for (int i = 0; i <= 9; i++)
            {
                std::cout << array[i] << '\n';
            }
        }
        else if (choice == 3)
        {
            std::cout << "Enter number indexes\n";
            int i, j;
            std::cin >> i >> j;
            if (i <= 9 && j <= 9)
            {
                Complex temp = array[i] + array[j];
                std::cout << temp << '\n';
            }
            else
            {
                std::cout << "Invalid input\n";
            }
        }
    }
}
int main()
{
    Complex C1;
    Complex C2(3, 7);
    C2.display();
    Complex C3(C2);
    C3.display();
    // Complex C4(C3.add(C2));
    // C1=C3.add(C2);
    C1.display();
    C1 = C3 + C2;
    int c = 2 + 3;
    C1 = C2 + c;
    C1.display();
    C1 = c + C2;
    C1.display();
    menu();
    return 0;
}
