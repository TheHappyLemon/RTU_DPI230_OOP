#include <iostream>
#include <list>
#include <algorithm>

// 1 variants.
// Artjoms Kucerjavijs 211RDB105
// LD7

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

class Firm {
private:
    list<Employee> employees;
    static bool CmpSal(const Employee& a, const Employee& b) {
        return a.GetAlga() < b.GetAlga();
    }
public:
    Firm();
    virtual ~Firm();
    void AddEmployee(const Employee& employee);
    void Print() const;
    double GetMaxSalary() const;
};

Firm::Firm(){}

Firm::~Firm() {
    employees.clear();
}

void Firm::AddEmployee(const Employee& employee) {
    employees.push_back(Employee(employee.GetName(), employee.GetGender(), employee.GetBirthYear(), employee.GetAlga()));
}

void Firm::Print() const {
    unsigned int i = 1;
    for (auto it = employees.cbegin(); it != employees.cend(); it++) {
        cout << i++ << ") ";
        it->Print();
        cout << "." << endl;
    }
}

double Firm::GetMaxSalary() const {


    if (!employees.size())
        throw - 1;
    else
        return max_element(employees.cbegin(), employees.cend(), CmpSal)->GetAlga();
}

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
    //string name, char gender, int birth_year, double alga
    Employee* emp1 = new Employee("Andrej", 'M', 1900, 721.15);
    Employee* emp2 = new Employee("Nikola", 'M', 1800, 500.15);
    Employee* emp3 = new Employee("Annita", 'W', 2000, 1000.50);
    Employee* emp4 = new Employee("Broken", 'B', 9999, 5555.55);
    Firm* firm = new Firm();
    double answ;
    try {
        firm->AddEmployee(*emp1);
        cout << "Employee " << emp1->GetName() << " added!" << endl;
        firm->AddEmployee(*emp2);
        cout << "Employee " << emp2->GetName() << " added!" << endl;
    }
    catch (...) {
        cout << "Exception...";
    }
    try {
        firm->AddEmployee(*emp3);
        cout << "Employee " << emp3->GetName() << " added!" << endl;
        firm->AddEmployee(*emp4);
        cout << "Employee " << emp4->GetName() << " added!" << endl;
    }
    catch (...) {
        cout << "Exception...";
    }

    firm->Print();
    answ = firm->GetMaxSalary();
    cout << endl << "Max salary = " << answ << endl << endl;
    delete firm;
    cout << "Press enter...";
    cin.get();
    return 0;
}