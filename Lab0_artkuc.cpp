#include <iostream>

// 1 variants.
// Artjoms Kucerjavijs 211RDB105

using namespace std;
class Human {
private:
    string name;
    char gender;
    int birth_year;
public:
    Human();
    Human(string, char, int);
    ~Human() {
        cout << this->gender << " " << this->name << " born in " << this->birth_year << " died" << endl;
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
    void Print() const;
    void FeelBad() const;
};

Human::Human() : name("Janis"), gender('m'), birth_year(1970) {
}

Human::Human(string name, char gender, int birth_year){
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
    // has to be quite an operation in reality :)
    this->gender = new_gender;
}

inline int Human::GetBirthYear() const {
    return this->birth_year;
}

inline void Human::SetBirthYear(int new_birth_year) {
    // how can human change his birth year?:)
    this->birth_year = new_birth_year;
}

inline void Human::Print() const {
    cout << "gender = " << this->gender  << ". name = " << this->name << ". birth_year = " << this->birth_year << endl;
}

inline void Human::FeelBad() const{
    cout << this->name << ": I don't feel so good..." << endl;
}


int main(void) {
    Human human1, human2("Artem", 'm', 1000), * human3;
    human3 = new Human("Roman", 'w', 2123);

    human1.Print(); 
    human2.Print(); 
    human3->Print(); 

    human1.SetName("Janchiks");
    human2.SetGender('M');
    human3->SetBirthYear(9999);

    cout << "\nSome time has passed...\n";

    human1.Print(); 
    human2.Print(); 
    human3->Print(); 

    cout << endl << "**************" << endl << endl;

    human3->FeelBad();
    delete human3;

    cout << "Press enter to kill others...";

    cin.get();
    return 0;
}
