#include <iostream>

// 1 variants.
// Artjoms Kucerjavijs 211RDB105
// LD3

using namespace std;

class OverflowException {
public:
    OverflowException() {
        cout << endl << "Exception created!" << endl;
    }
    ~OverflowException() {
        cout << "Exception finished!" << endl;
    }
};

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
    typedef Employee* EPPointer;
    EPPointer *employees;
    static const unsigned int MAX_LENGTH = 5;
    unsigned int maxLen;
    unsigned int curLen;
public:
    Firm();
    Firm(unsigned int maxLen);
    virtual ~Firm();
    int GetMaxLen() const;
    int GetCurLen() const;
    void AddEmployee(const Employee& employee);
    void Print() const;
    double GetMaxSalary() const;
};

Firm::Firm() : maxLen(MAX_LENGTH), curLen(0){}

Firm::Firm(unsigned int maxLen) : curLen(0) {
    this->maxLen = maxLen;
    employees = new EPPointer[maxLen];
}

Firm::~Firm() {
    cout << "Firm deleted" << endl;
    for (unsigned int i = 0; i < curLen; ++i) {
        delete employees[i];
    }
    delete[] employees;
}

int Firm::GetMaxLen() const {
    return this->maxLen;
}

int Firm::GetCurLen() const {
    return this->curLen;
}

void Firm::AddEmployee(const Employee& employee) {
    cout << curLen << endl;
    if (curLen >= maxLen || curLen < 0) {
        throw OverflowException();
        return;
    }
    employees[curLen++] = new Employee
    (
        employee.GetName(), employee.GetGender(),
        employee.GetBirthYear(), employee.GetAlga()
    );
}

void Firm::Print() const {
    for (unsigned int i = 0; i < curLen; ++i) {
        cout << (i + 1) << ") ";
        employees[i]->Print();
        cout << '\n';
    }
}

double Firm::GetMaxSalary() const {

    double res = 0.0;
    double curSal;

    if (curLen < 1) {
        cout << "No employees, can not get maximum salary" << endl;
        return -1.0;
    }    
    for (unsigned int i = 0; i < curLen; i++) {
        curSal = employees[i]->GetAlga();
        if (curSal > res) {
            res = curSal;
        }
    }
    return res;
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
    Firm* firm = new Firm(3);
    double answ;
    try {
        firm->AddEmployee(*emp1);
        cout << "Employee " << emp1 -> GetName() << " added!" << endl;
        firm->AddEmployee(*emp2);
        cout << "Employee " << emp2 -> GetName() << " added!" << endl;
    }
    catch (const OverflowException&) {
        cout << "Exception...";
    }

    cout << "maxLen = " << firm->GetMaxLen() << endl;
    cout << "curLen = " << firm->GetCurLen() << endl;

    try {
        firm->AddEmployee(*emp3);
        cout << "Employee " << emp3->GetName() << " added!" << endl;
        firm->AddEmployee(*emp4);
        cout << "Employee " << emp4->GetName() << " added!" << endl;
    }
    catch (const OverflowException&) {
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