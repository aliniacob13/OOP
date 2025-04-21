#include <iostream>
#include <string>
#include <vector>
class Experience
{
    int years;
    std::string last_function;

public:
    Experience(int years, std::string last_function) : years(years), last_function(last_function) {}
    int getYears() { return years; }
    std::string getLastFunction() { return last_function; }
    void setYears(int ani) { years = ani; }
    void setLastFunction(const std::string &functie) { last_function = functie; }
};
class Person
{
    std::string name;
    int age;

public:
    Person(std::string name, int age) : name(name), age(age) {}
    std::string getName() { return name; }
    int getAge() { return age; }
    void setName(std::string &nume) { name = nume; }
    void setAge(int varsta) { age = varsta; }
    virtual void displayInfo() = 0;
    virtual ~Person() {std::cout<<"Destructor Person\n";};
};
class Teacher : virtual public Person
{
    std::string subject;

public:
    Teacher(std::string name, int age, std::string subject) : Person(name, age), subject(subject) {}
    std::string getSubject() { return subject; }
    void setSubject(std::string &materie) { subject = materie; }
    void displayInfo() override
    {
        std::cout << "Teacher: " << getName() << ", Varsta: " << getAge() << ", Subiect: " << getSubject() << std::endl;
    }
    //~Teacher() {std::cout<<"Destructor Teacher\n";};
};
class Administrator : virtual public Person
{
    std::string department;

public:
    Administrator(std::string name, int age, std::string department) : Person(name, age), department(department) {}
    std::string getDepartment() const { return department; }
    void setDepartment(std::string &departament) { department = departament; }
    void displayInfo() override
    {
        std::cout << "Administrator: " << getName() << ", Varsta: " << getAge() << ", Department: " << getDepartment() << std::endl;
    }
    //~Administrator() {std::cout<<"Destructor Administrator\n";};
};
class HeadofDepartment : public Teacher, public Administrator
{
    Experience experience;

public:
    HeadofDepartment(std::string name, int age, std::string subject, std::string department, int years, std::string last_function)
        : Person(name, age), Teacher(name, age, subject), Administrator(name, age, department), experience(years, last_function) {}
    void displayInfo() override
    {
        std::cout << "Head of Department: " << getName() << ", Varsta: " << getAge() << ", Subiect: " << getSubject() << ", Department: " << getDepartment() << ", Experience: " << experience.getYears() << " ani in " << experience.getLastFunction() << std::endl;
    }
    //~HeadofDepartment() {std::cout<<"Destructor HeadofDepartment\n";};
};
int main()
{
    std::vector<Person *> staff;
    Person *admin = new Administrator("Liviu", 30, "Computer Science");
    Person *sfetcu = new Teacher("Razvan Sfetcu", 35, "Mathematics");
    Person *dobrovat = new Teacher("Anca Dobrovat", 40, "Computer Science");
    Person *paun = new HeadofDepartment("Andrei Paun", 45, "Computer Science", "Science", 20, "Lector Universitar");
    staff.push_back(admin);
    staff.push_back(sfetcu);
    staff.push_back(dobrovat);
    staff.push_back(paun);

    for (auto &person : staff)
        person->displayInfo();
    std::cout << std::endl;

    for (auto &person : staff)
        delete person;
    return 0;
}
