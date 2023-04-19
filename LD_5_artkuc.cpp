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

template <class T>
class Human {
protected:
    string name;
    T gender;
    int birth_year;
public:
    Human();
    Human(string, T, int);
    virtual ~Human() {
        cout << "Human: " << this->gender << " " << this->name << " born in " << this->birth_year << " died" << endl;
    }
    // getters
    string GetName() const {
        return this->name;
    }
    T GetGender() const {
        return this->gender;
    }
    int GetBirthYear() const {
        return this->birth_year;
    }
    // setters
    void SetName(string name) {
        this->name = name;
    };
    void SetGender(string gender) {
        this->gender = gender;
    };
    void SetBirthYear(T year) {
        this->birth_year = year;
    };
    // methods
    virtual void Print() const;
    void FeelBad() const;
};

template <class T>
class Employee : public Human<T> {
private:
    double alga;
public:
    Employee();
    Employee(string, T, int, double);
    double GetAlga() const;
    void SetAlga(double alga);
    virtual ~Employee() {
        cout << "Employee: " << this->gender << " " << this->name << " born in " << this->birth_year << " with salaray " << this->alga << " died" << endl;
    }
    virtual void Print() const;
};
template <class T>
class Firm {
private:
    typedef Employee<T>* EPPointer;
    EPPointer* employees;
    static const unsigned int MAX_LENGTH = 5;
    unsigned int maxLen;
    unsigned int curLen;
public:
    Firm();
    Firm(unsigned int maxLen);
    virtual ~Firm();
    int GetMaxLen() const;
    int GetCurLen() const;
    void AddEmployee(const Employee<T>& employee);
    void Print() const;
    double GetMaxSalary() const;
};

template <class T>
Firm<T>::Firm() : maxLen(MAX_LENGTH), curLen(0) {}

template <class T>
Firm<T>::Firm(unsigned int maxLen) : curLen(0) {
    this->maxLen = maxLen;
    employees = new EPPointer[maxLen];
}

template <class T>
Firm<T>::~Firm() {
    cout << "Firm deleted" << endl;
    for (unsigned int i = 0; i < curLen; ++i) {
        delete employees[i];
    }
    delete[] employees;
}

template <class T>
int Firm<T>::GetMaxLen() const {
    return this->maxLen;
}

template <class T>
int Firm<T>::GetCurLen() const {
    return this->curLen;
}

template <class T>
void Firm<T>::AddEmployee(const Employee<T>& employee) {
    if (curLen >= maxLen || curLen < 0) {
        throw OverflowException();
        return;
    }
    employees[curLen++] = new Employee<T>
    (
        employee.GetName(), employee.GetGender(),
        employee.GetBirthYear(), employee.GetAlga()
    );
}

template <class T>
void Firm<T>::Print() const {
    for (unsigned int i = 0; i < curLen; ++i) {
        cout << (i + 1) << ") ";
        employees[i]->Print();
        cout << '\n';
    }
}

template <class T>
double Firm<T>::GetMaxSalary() const {

    double res = 0.0;
    double curSal;

    if (curLen < 1) {
        cout << "No employees, can not get maximum salary" << endl;
        return -1.0;
    }
    else {
        for (unsigned int i = 0; i < curLen; i++) {
            curSal = employees[i]->GetAlga();
            if (curSal > res) {
                res = curSal;
            }
        }
    }
    return res;
}

template <class T>
Employee<T>::Employee() : Human<T>(), alga(0) {
}

template <class T>
Employee<T>::Employee(string name, T gender, int birth_year, double alga) : Human<T>(name, gender, birth_year) {
    this->alga = alga;
}

template <class T>
inline void Employee<T>::SetAlga(double alga) {
    this->alga = alga;
}

template <class T>
inline double Employee<T>::GetAlga() const {
    return this->alga;
}

template <class T>
inline void Employee<T>::Print() const {
    Human<T>::Print();
    cout << ". salary = " << this->alga;
}

template <class T>
Human<T>::Human() : name("Janis"), gender('m'), birth_year(1970) {
}

template <class T>
Human<T>::Human(string name, T gender, int birth_year) {
    this->name = name;
    this->gender = gender;
    this->birth_year = birth_year;
}

template <class T>
inline void Human<T>::Print() const {
    cout << "gender = " << this->gender << ". name = " << this->name << ". birth_year = " << this->birth_year;
}

template <class T>
inline void Human<T>::FeelBad() const {
    cout << this->name << ": I don't feel so good..." << endl;
}


int main(void) {
    //string name, char gender, int birth_year, double alga
    Employee<char>* emp1 = new Employee<char>("Andrej", 'M', 1900, 800.12);
    Employee<unsigned char>* emp2 = new Employee<unsigned char>("Nikola", 'M', 1800, 500.15);
    Employee<char>* emp3 = new Employee<char>("Annita", 'W', 2000, 1000);
    Employee<unsigned char>* emp4 = new Employee<unsigned char>("Broken", 'B', 9999, 5555.55);
    Firm<char>* firm = new Firm<char>(3);
    Firm<unsigned char>* firm1 = new Firm<unsigned char>(3);
    double answ;
    try {
        firm->AddEmployee(*emp1);
        cout << "Employee " << emp1->GetName() << " added!" << endl;
        firm->AddEmployee(*emp3);
        cout << "Employee " << emp2->GetName() << " added!" << endl;
    }
    catch (const OverflowException&) {
        cout << "Exception...";
    }

    cout << "maxLen = " << firm->GetMaxLen() << endl;
    cout << "curLen = " << firm->GetCurLen() << endl;

    try {
        firm1->AddEmployee(*emp2);
        cout << "Employee " << emp3->GetName() << " added!" << endl;
        firm1->AddEmployee(*emp4);
        cout << "Employee " << emp4->GetName() << " added!" << endl;
    }
    catch (const OverflowException&) {
        cout << "Exception...";
    }

    firm->Print();
    answ = firm->GetMaxSalary();
    cout << endl << "Max salary(firm) = " << answ << endl << endl;
    firm1->Print();
    answ = firm1->GetMaxSalary();
    cout << endl << "Max salary(firm1) = " << answ << endl << endl;
    delete firm;
    delete firm1;
    cout << "Press enter...";
    cin.get();
    return 0;
}