#include <iostream>

// 1 variants.
// Artjoms Kucerjavijs 211RDB105
// LD2

using namespace std;
class Human {
protected:
    string name;
    char gender;
    int birth_year;
public:
    Human();
    Human(string, char, int);
    virtual ~Human() {
        cout << "Human: " << this->gender << " " << this->name << " born in " << this->birth_year << " died" << endl;
    }
    // getters
    string GetName()      const;
    char GetGender()    const;
    int    GetBirthYear() const;
    // setters
    void SetName(string);
    void SetGender(char);
    void SetBirthYear(int);
    // methods
    virtual void Print() const;
    void FeelBad() const;
};

class Employee : public Human {
private:
    double alga;
public:
    Employee();
    Employee(string, char, int, double);
    double GetAlga() const;
    void SetAlga(double alga);
    virtual ~Employee() {
        cout << "Employee: " << this->gender << " " << this->name << " born in " << this->birth_year << " with salaray " << this->alga << " died" << endl;
    }
    virtual void Print() const;
};

Employee::Employee() : Human(), alga(0) {
}

Employee::Employee(string name, char gender, int birth_year, double alga) : Human(name, gender, birth_year) {
    this->alga = alga;
}

inline void Employee::SetAlga(double alga) {
    this->alga = alga;
}

inline double Employee::GetAlga() const {
    return this->alga;
}

inline void Employee::Print() const {
    Human::Print();
    cout << ". salary = " << this->alga;
}

Human::Human() : name("Janis"), gender('m'), birth_year(1970) {
}

Human::Human(string name, char gender, int birth_year) {
    this->name = name;
    this->gender = gender;
    this->birth_year = birth_year;
}

inline string Human::GetName() const {
    return this->name;
}

inline void Human::SetName(string new_name) {
    this->name = new_name;
}

inline char Human::GetGender() const {
    return this->gender;
}

inline void Human::SetGender(char new_gender) {
    this->gender = new_gender;
}

inline int Human::GetBirthYear() const {
    return this->birth_year;
}

inline void Human::SetBirthYear(int new_birth_year) {
    this->birth_year = new_birth_year;
}

inline void Human::Print() const {
    cout << "gender = " << this->gender << ". name = " << this->name << ". birth_year = " << this->birth_year;
}

inline void Human::FeelBad() const {
    cout << this->name << ": I don't feel so good..." << endl;
}


int main(void) {
    const int N = 4;
    Human* people[N] = {
        new Human(),
        new Human("Andrej", 'M', 1999),
        new Employee(),
        new Employee("Nikolaj", 'M', 2001, 1500)
    };

    for (int i = 0; i < N; i++) {
        cout << (i+1) << ") ";
        people[i]->Print();
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        delete people[i];
    }


    cout << "Press enter...";

    cin.get();
    return 0;
}