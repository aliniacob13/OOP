///EXCEPTII
/*
try{
    //conditii eroare
    throw ... 
} catch(*){
 ...
 } //orice tip de date existent(int, char, float etc), obiecte de tipuri definite de utilizator, obiecte de tip excetion
  //obiecte de tip exception -> logic_error
                                    ->%0
                                    ->out_of_range
                             -> runtime_error
                                    ->overflow_error
                                    ->underflow_error
                            ->bad_alloc
                            ->my_exception(string) ->what
    class ExceptiiCustom: public exception{
        public:
            const char* what() const noexcept override{
                return "Exceptie personalizata";
            }


    SMART POINTERS
    ->unique_ptr
    ->shared_ptr
    ->weak_ptr
*/
/*
1.Definiti o clasa de baza din care se deriva o alta clasa de baza(alocare dinamica)
2.Provocati exceptii in constructori si destructori. Ce se intampla?
3.Faceti in main() o succesiune de catch-uri pentru int, char*, referinta la clasa de baza, la cea derivata
Sa se poata vedea functionalitatea pe toate catch-urile
*/
#include<iostream>
#include<string>
class Base{
    private:
        std::string name;
        int age;
        char* address;
    public:
        Base(){
            try{
                std::cout<<"Constructor Base\n";
                name = "Base";
                age = 0;
                address = new char[50];
                if(!address)
                    throw std::bad_alloc();
            } catch(std::bad_alloc& e){
                std::cerr << "Memory allocation failed: " << e.what() << '\n';
            }
            catch(std::exception& e){
                std::cerr << "Exception: " << e.what() << '\n';
            }
            catch(...){
                std::cerr << "Unknown exception occurred\n";
            }
            
        }
        virtual ~Base(){
            std::cout<<"Destructor Base\n";
        }
        virtual void display() const{
            std::cout<<"Base class\n";
        }
};
class Derived: public Base{
    public:
        Derived(){
            std::cout<<"Constructor Derived\n";
        }
        ~Derived(){
            std::cout<<"Destructor Derived\n";
        }
        void display() const override{
            std::cout<<"Derived class\n";
        }
};
class CustomException: public std::exception{
    public:
        const char* what() const noexcept override{
            return "Custom exception occurred";
        }
};
int main(){
    
    return 0;
}