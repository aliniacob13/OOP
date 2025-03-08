// a si b naturale. Sa se det. cel mai mic si cel mai mare nr. din [a,b]
//  care are nr.maxim de divizori
/*
#include <iostream>
#include<climits>
using namespace std;
int a,b,i,nrdiv,d,nrmax,mini,maxi,ok,mini_nr=INT_MAX,maxi_nr;
int main()
{
    cin>>a>>b;
    for(i=a;i<=b;i++)
    {
        nrdiv=2;
        for(d=2;d<=i/2;d++)
        {
            if(i%d==0)
            {
                nrdiv++;
            }
        }
        if(nrdiv>nrmax)
        {
            mini_nr=maxi_nr=i;
            nrmax=nrdiv;
        }
        else if(nrdiv==nrmax)
            {
                maxi_nr=i;
            }
    }
    cout<<mini_nr<<" "<<maxi_nr;
    return 0;
}
*/
// 2.Se da un sir s format din litere mici cu cuvinte separarte printr-un spatiu. Afisati-le
// in ordine inversa
/*
#include<iostream>
#include<cstring>
using namespace std;
int k,i;
char s[101],a[101][20],*p;
int main()
{
    cin.getline(s,101);
    p=strtok(s," ");
    while(p)
    {
        strcpy(a[k++],p);
        p=strtok(NULL," ");
    }
    for(i=k-1;i>=0;i--)
        cout<<a[i]<<" ";
    return 0;
}
*/
// 3. problema spectacolelor
/*
#include<iostream>
using namespace std;
int inceput[100],final[100],contor=1,n,i,j,last;
int main()
{
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>inceput[i]>>final[i];
    }
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            {
                if(final[i]>final[j])
                    {swap(final[i],final[j]);
                    swap(inceput[i],inceput[j]);
                    }
            }
    last=final[0];
    for(i=0;i<n;i++)
    {
        if(inceput[i]>=last)
        {
            contor++;
            last=final[i];
        }
    }
    cout<<contor;
    return 0;
}
*/

/// CLASE
#include<iostream>
//using namespace std;

/*
class class_name
{
    acces_specifier_1 : //(poate fi public, private, protected)
                        member1;
    acces_specifier_2 : member2;
};
*/

class Car
{
private:
    int year;
    char name[30]="";

public:
    // constructor de initializare. Ex: Car(); Car(int year); Car(int year, char name[]);
    Car(){}
    
    // constructor de copiere. Ex: Car(Car obj);
    // destructor. Ex: ~Car(){delete name;};

    // seteri
    void set_year(int new_year)
    {
        year = new_year;
    }
    void set_name(char new_name[])
    {
        strcpy(name, new_name);
    }
    // getteri
    int get_year()
    {
        return year;
    }

    char *get_name()
    {
        return name;
    }

    void display_info(Car obj)
    {
        std::cout << "Year of construction: " << obj.year <<"\n";
        std::cout << "Model " << obj.name << "\n";
    }
    ///putem pune Car::Car(int year, char name[]) in afara clasei
};
int main()
{
    Car car;
    //Car car1(2020,"Audi");
    //Car car2(2020);
    std::cout<<"Year of construction: "<<car.get_year()<<"\n";
    return 0;
}