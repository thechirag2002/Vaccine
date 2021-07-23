#include <iostream>
#include <cstring>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#define TOTAL_VACCINE 100

using namespace std;

void menu();
int password();
class person
{
protected:
    char gender[10];
    char name[100];
    int age;
    char adhaar[12];
    static int k;

public:
    virtual void get_data() = 0;

    person()
    {
        strcpy(gender, "xxxxx");
        strcpy(name, "xxxxx");
        age = 0;
        strcpy(adhaar, "000000000");
    }
};

class patient : protected person
{
    float temperature;
    string profession;
    int dose;
    string Attendee;

public:
    int center_no;
    void update_record(char *);
    void get_data();
    void add_person();
    void display();
    void show_patient_data();
    void search_patient_by_name(char *);
    void search_patient_by_adhaar(char *);
    void search_patient_by_age(int, int);
    void search_patient_by_gender(char *);
    inline int get_dose()
    {
        return dose;
    }

    patient()
    {
        temperature = 98.6;
        profession = "NA";
        dose = 0;
        Attendee = "NIL";
    }
};

class center
{
protected:
    string center_name;
    int total_vaccine;
    int applied_vaccine;
    int center_no;
    static int k;
    //int f_var;
    //int s;

public:
    void display_available();
    void display_applied();
    void add_vaccine();
    void show_center();
    void incrementApplied();
    inline int getTotal()
    {
        return total_vaccine;
    }
    inline int getApplied()
    {
        return applied_vaccine;
    }
    center()
    {
    }
    center(string c_name)
    {
        // total_vaccine = TOTAL_VACCINE;
        center_no = k;
        k++;
        if (k - 1 == 1)
        {
            ifstream myfile("count1.txt");
            if (!myfile)
            {
                total_vaccine = TOTAL_VACCINE;
                ofstream myfile("count1.txt");
                myfile << total_vaccine;
                myfile.close();
            }
            else
            {
                myfile >> total_vaccine;
                myfile.close();
            }
        }
        else if (k - 1 == 2)
        {
            ifstream myfile("count2.txt");
            if (!myfile)
            {
                total_vaccine = TOTAL_VACCINE;
                ofstream myfile("count2.txt");
                myfile << total_vaccine;
                myfile.close();
            }
            else
            {
                myfile >> total_vaccine;
                myfile.close();
            }
        }
        else if (k - 1 == 3)
        {
            ifstream myfile("count3.txt");
            if (!myfile)
            {
                total_vaccine = TOTAL_VACCINE;
                ofstream myfile("count3.txt");
                myfile << total_vaccine;
                myfile.close();
            }
            else
            {
                myfile >> total_vaccine;
                myfile.close();
            }
        }
        center_name = c_name;
        applied_vaccine = 0;
        ifstream ind;
        ind.open("Patient_Data.dat", ios::in | ios::binary);
        // ind.seekg(0,ios::beg);
        if (!ind)
        {
            cout << "****";
        }
        else
        {
            patient *p = new patient();
            ind.read((char *)p, sizeof(*p));
            // cout<<ind.tellg();
            while (!ind.eof())
            {
                if (p->center_no == k - 1)
                {
                    applied_vaccine += p->get_dose();
                }
                ind.read((char *)p, sizeof(*p));
            }
            ind.close();
            //  delete (p);
        }
    }

    int operator+(center c)
    {
        int total = 0;
        //total=total_vaccine;
        total += total_vaccine + c.total_vaccine;
        total = total - applied_vaccine - c.applied_vaccine;
        return (total);
    }
    int operator+(int c)
    {
        int total;
        total = total_vaccine + c - applied_vaccine;
        return (total);
    }
};
int center::k = 1;
void center::show_center()
{

    cout << center_name;
}

void center::display_available()
{
    //cout << total_vaccine << " " << applied_vaccine << endl;
    cout << "\n\nAvailable number of vaccines are " << total_vaccine - applied_vaccine;
}

void center::display_applied()
{

    cout << "Total number of Applied Vaccines are :- " << applied_vaccine;
}

void center::add_vaccine()
{
    ofstream ind;
    string path = "count" + to_string(center_no) + ".txt";
    ind.open(path);
    int add;
    cout << "\t Enter number of vaccines you want to add : ";
    cin >> add;
    total_vaccine += add;
    ind << total_vaccine;
    cout << "\n\n\t\tSUCCESSFULLY ADDED VACCINES TO THE STOCK\n";
    ind.close();
}
void center::incrementApplied()
{
    applied_vaccine++;
}
///////////////////////////////////////////////////
class nurse : protected person
{
protected:
    char identification_id[100];
    char specialization[100];
    char center[100];

public:
    void get_data();
    void add_nurse();
    void search_nurse_by_id(char *);
    void display();
    void show_nurse_data();
    void search_nurse_by_center(char *);

    nurse()
    {
        strcpy(identification_id, "000");
        strcpy(specialization, "NULL");
        strcpy(center, "xxx");
    }
};
void nurse::get_data()
{
    cout << "Enter name : ";
    fflush(stdin);
    cin.getline(name, 25);
    cout << "\nEnter Identification number : ";
    fflush(stdin);
    cin >> identification_id;
C:
    cout << "\nEnter adhaar no. : ";
    cin >> adhaar;

    try
    {
        if (strlen(adhaar) != 12)
            throw(1);
    }
    catch (int x)
    {
        cerr << "INVALID ADHAAR NUMBER";
        goto C;
    }

    cout << "\nEnter Gender (M/F) : ";
    cin >> gender;
    cout << "\nEnter age : ";
    cin >> age;
    cout << "\nEnter specialization : ";
    fflush(stdin);
    cin.getline(specialization, 40);
    cout << "\nEnter center allotted : ";
    cin >> center;
}
void nurse::add_nurse()
{
    ofstream fout;
    fout.open("Nurse_Data.dat", ios::app | ios::binary);
    fout.write((char *)this, sizeof(*this));
    fout.close();
}
void nurse::show_nurse_data()
{
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Nurse name : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << name;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Identification number : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << identification_id;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Adhaar no. : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << adhaar;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Gender : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << gender;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Age : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << age;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Specialization : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << specialization;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(28);
    cout << endl
         << "Center allotted : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << center << endl
         << endl;
}

void nurse::display()
{
    ifstream fin;
    fin.open("Nurse_Data.dat", ios::in | ios::binary);
    if (!fin)
        cout << "\nFile not found!";
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            show_nurse_data();
            fin.read((char *)this, sizeof(*this));
        }
    }
}

void nurse::search_nurse_by_id(char *n)
{
    int count = 0;
    ifstream fin;
    fin.open("Nurse_Data.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found ";
    }
    else
        fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (!strcmp(n, identification_id))
        {
            count++;
            show_nurse_data();
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (count == 0)
        cout << "\nRecord not found\n";
    fin.close();
}

void nurse::search_nurse_by_center(char *n)
{
    int count = 0;
    ifstream fin;
    fin.open("Nurse_Data.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found ";
    }
    else
        fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (!strcmp(n, center))
        {
            count++;
            show_nurse_data();
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (count == 0)
        cout << "\nRecord not found\n";
    fin.close();
}

//=========================================

void patient::get_data()
{
A:
    cout << "\nEnter name:";
    fflush(stdin);
    cin.getline(name, 100);
    cout << "\nEnter adhaar no.";
    cin >> adhaar;
    try
    {
        if (strlen(adhaar) != 12)
            throw(adhaar);
    }
    catch (char[])
    {
        cerr << "INVALID ADHAAR NUMBER";
        goto A;
    }
    cout << "\nEnter Gender(M or F):";
    cin >> gender;
    cout << "\nEnter age:";
    cin >> age;
    cout << "\nEnter Dose:";
    cin >> dose;
    cout << "\nEnter temperature (in degree Fahrenheit): ";
    cin >> temperature;
    cout << "\nVaccinated By:";
    fflush(stdin);
    getline(cin, Attendee);
}

void patient::add_person()
{
    ofstream fout;
    fout.open("Patient_Data.dat", ios::app | ios::binary);
    fout.write((char *)this, sizeof(*this));
    fout.close();
}

void patient::show_patient_data()
{
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Name : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << name;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Adhaar no : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << adhaar;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Gender : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << gender;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Age : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << age;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Dose : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << dose;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Temperature : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << temperature;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Vaccinated By : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << Attendee;
    cout.setf(ios::right, ios::adjustfield);
    cout.width(20);
    cout << endl
         << "Center Number : ";
    cout.setf(ios::right, ios::adjustfield);
    cout.width(25);
    cout << setfill(' ') << center_no;
    cout << endl
         << endl;
}

void patient::display()
{
    ifstream fin;
    fin.open("Patient_Data.dat", ios::in | ios::binary);
    if (!fin)
        cout << "\nFile not found!";
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            show_patient_data();
            fin.read((char *)this, sizeof(*this));
        }
    }
    fin.close();
}

void patient::search_patient_by_name(char *n)
{
    int count = 0;
    ifstream fin;
    fin.open("Patient_Data.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found ";
    }
    else
        fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (!strcmp(n, name))
        {
            count++;
            show_patient_data();
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (count == 0)
        cout << "\nRecord not found\n";
    fin.close();
}

void patient::search_patient_by_adhaar(char *n)
{
    // cout<<n;
    int count = 0;
    ifstream fin;
    fin.open("Patient_Data.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found ";
    }
    else
        fflush(stdin);
    fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (!strcmp(n, adhaar))
        {
            count++;
            show_patient_data();
            break;
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (count == 0)
        cout << "\nRecord not found\n";
    fin.close();
}

void patient::search_patient_by_gender(char *n)
{
    int count = 0;
    ifstream fin;
    fin.open("Patient_Data.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found ";
    }
    else
        fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (!strcmp(n, gender))
        {
            count++;
            show_patient_data();
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (count == 0)
        cout << "\nRecord not found\n";
    fin.close();
}

void patient::search_patient_by_age(int l, int u)
{
    int count = 0;
    ifstream fin;
    fin.open("Patient_Data.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found ";
    }
    else
        fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (age >= l && age <= u)
        {
            count++;
            show_patient_data();
        }
        fin.read((char *)this, sizeof(*this));
    }
    if (count == 0)
        cout << "\nRecord not found\n";
    fin.close();
}

void patient::update_record(char *adhaar)
{
    fstream file;
    file.open("Patient_Data.dat", ios::in | ios::out | ios::binary | ios::ate);
    file.seekg(0);
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        if (!strcmp(adhaar, this->adhaar))
        {
            dose++;
            file.seekp(file.tellp() - sizeof(*this));
            file.write((char *)this, sizeof(*this));
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
}

//=====================================================

int main()
{

B:
    system("cls");
    cout << "\n\n\t\t\t\t*********************************************";
    cout << "\n\t\t\t\t\tEnter User name and Password\n";
    cout << "\t\t\t\t*********************************************\n";
    int attempt = 3;
    while (attempt >= 1)
    {
        int pass = password();
        if (pass == 1)
            break;
        else
            cout << "\n\n\t\t Wrong Password Or User Name \n\n\t\t You Can try Only " << attempt - 1 << " times more";
        attempt--;
        if (attempt < 1)
        {
            for (int i = 59; i >= 0; i--)
            {
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tYOU ARE BLOCKED FOR 1 MINUTE!!";
                cout << "\n\n\n\n\n\n\t\t\t\t\tTRY AFTER " << i << " SECONDS.....";
                Sleep(1000);
            }
            attempt = 3;
            goto B;
        }
    }
    center cobj1("Lok Naayak Jai Prakash Hospital(LNJP)");
    center cobj2("Government Polyclinic Sector 4");
    center cobj3("UPHC Krishna Nagar Gamri");
    patient pobj;
    nurse nobj;
    int choice;
    do
    {
        menu();
        cout << "\n\nEnter your Choice :- ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            cout << "\n\nVarious Vaccination Centers in Kurukshetra city are given below :" << endl;
            cobj1.show_center();
            cout << endl;
            cobj2.show_center();
            cout << endl;
            cobj3.show_center();
            break;
        case 2:
        {
            system("cls");
            cout << "CENTER 1:Lok Naayak Jai Prakash Hospital(LNJP) \nCENTER 2:Government Polyclinic Sector 4\nCENTER 3:UPHC Krishna Nagar Gamri\n";
            cout << "\n\nFrom which center no. is the patient vaccinated ";
            cin >> pobj.center_no;
            int flag = 1;
            if (pobj.center_no == 1)
            {
                if (cobj1.getTotal() == cobj1.getApplied())
                {
                    flag = 0;
                }
            }
            else if (pobj.center_no == 2)
            {
                if (cobj2.getTotal() == cobj2.getApplied())
                {
                    flag = 0;
                }
            }
            else
            {
                if (cobj3.getTotal() == cobj3.getApplied())
                {
                    flag = 0;
                }
            }
            if (flag == 0)
            {
                cout << "Sorry vaccines are not available in this center";
            }
            else
            {

                pobj.get_data();
                pobj.add_person();
                if (pobj.center_no == 1)
                {
                    cobj1.incrementApplied();
                }
                else if (pobj.center_no == 2)
                {
                    cobj2.incrementApplied();
                }
                else
                {
                    cobj3.incrementApplied();
                }
                cout << "\n\n\tDATA SUCCESSFULLY SAVED\n";
            }
            break;
        }
        case 3:
            system("cls");
            {
                char ch1;
                cout << "Press A to search patient data by individual..\nPress B to search patient data by category..\n\n";
                cout << "Enter your choice :  ";
                cin >> ch1;
                switch (ch1)
                {
                case 'A':
                    system("cls");
                    char ch2;
                    cout << "\nPress a to search the patient data by name..\nPress b to search patient data by adhaar..\n";
                    cout << "\nEnter your choice :  ";
                    cin >> ch2;
                    switch (ch2)
                    {
                    case 'a':
                        char Name[30];
                        cout << "\nEnter patient name : ";
                        fflush(stdin);
                        cin.getline(Name, 30);
                        pobj.search_patient_by_name(Name);
                        break;
                    case 'b':
                        char Adhaar[20];
                        cout << "\nEnter patient's adhaar number : ";
                        cin >> Adhaar;
                        pobj.search_patient_by_adhaar(Adhaar);
                        break;
                    }
                    break;
                case 'B':
                    system("cls");
                    char ch3;
                    cout << "Press a to search the patient data by age..\nPress b to search patient data by gender..\n\n";
                    cout << "Enter your choice :  ";
                    cin >> ch3;
                    switch (ch3)
                    {
                    case 'a':
                        int l, u;
                        cout << "\nEnter the lower limit and upper limit of the age to be searched :\n ";
                        cout << "Lower Limit : ";
                        cin >> l;
                        cout << "\nUpper Limit : ";
                        cin >> u;
                        pobj.search_patient_by_age(l, u);
                        break;
                    case 'b':
                        char G[10];
                        cout << "\nEnter gender(M for male and F for female) : ";
                        cin >> G;
                        pobj.search_patient_by_gender(G);
                        break;
                    }
                    break;
                }
            }
            break;

        case 4:
            system("cls");
            {
                char Adhaar_no[20];
                cout << "\nEnter patient Adhaar number :- ";
                cin >> Adhaar_no;
                pobj.search_patient_by_adhaar(Adhaar_no);
                if (pobj.center_no == 1)
                {
                    if (cobj1.getTotal() == cobj1.getApplied())
                    {
                        cout << "Sorry vaccines are not available..";
                    }
                    else
                    {
                        cobj1.incrementApplied();
                        pobj.update_record(Adhaar_no);
                    }
                }
                else if (pobj.center_no == 2)
                {
                    if (cobj2.getTotal() == cobj2.getApplied())
                    {
                        cout << "Sorry vaccines are not available..";
                    }
                    else
                    {
                        cobj2.incrementApplied();
                        pobj.update_record(Adhaar_no);
                    }
                }
                else if (pobj.center_no == 3)
                {
                    if (cobj3.getTotal() == cobj3.getApplied())
                    {
                        cout << "Sorry vaccines are not available..";
                    }
                    else
                    {
                        cobj3.incrementApplied();
                        pobj.update_record(Adhaar_no);
                    }
                }
                cout << "\nSuccessfully Updated the record\n";
            }
            break;
        case 5:
            system("cls");
            {
                cout << "For center 1 :\n";
                cobj1.add_vaccine();
                cout << "\n\n";
                cout << "For center 2 :\n";
                cobj2.add_vaccine();
                cout << "\n\n";
                cout << "For center 3 :\n";
                cobj3.add_vaccine();
                cout << "\n\n";
            }
            break;
        case 6:
            system("cls");
            {
                cout << "For center 1\t";
                cobj1.display_available();
                cout << "\n\n";
                cout << "For center 2\t";
                cobj2.display_available();
                cout << "\n\n";
                cout << "For center 3\t";
                cobj3.display_available();
                cout << "\n\n\n";
                cout << "Total number of vaccines available in all the three centers are ";
                int total_vaccine_in_city = cobj1 + (cobj2 + cobj3);
                cout << total_vaccine_in_city << endl;
            }
            break;
        case 7:
            system("cls");
            {
                cout << "For Center 1 : \n";
                cobj1.display_applied();
                cout << "\n\n";
                cout << "For Center 2 : \n";
                cobj2.display_applied();
                cout << "\n\n";
                cout << "For Center 3 : \n";
                cobj3.display_applied();
                cout << "\n\n";
            }
            break;
        case 8:
        {
            system("cls");
            nobj.get_data();
            nobj.add_nurse();
            cout << "\n\n\tDATA SUCCESSFULLY SAVED ";
        }
        break;
        case 9:
        {
            system("cls");
            cout << "Press X to search nurse data by identification id.. \nPress Y to search nurse data by center..\nPress Z to display nurse data..\n";
            char ch4;
            cout << "Enter your Choice : ";
            cin >> ch4;
            switch (ch4)
            {
            case 'X':
            {
                char search_id[20];
                cout << "\nEnter nurse identification id :- ";
                cin >> search_id;
                nobj.search_nurse_by_id(search_id);
            }
            break;
            case 'Y':
            {
                char center[20];
                cout << "\nEnter nurse's center :- ";
                cin >> center;
                nobj.search_nurse_by_center(center);
            }
            break;
            case 'Z':
            {
                nobj.display();
            }
            break;
            }
        }
        break;
        case 10:
            system("cls");
            cout << "\n\n\tTHANKS FOR VISITNG..HAVE A NICE DAY :)\n";
            exit(0);
            break;
        default:
            cout << "\n\n\tTHANKS FOR VISITNG..HAVE A NICE DAY :)\n";
        }

    } while (choice > 0 && choice < 10);
}

void menu()
{
    cout << "\n\n\t\t\tPRESS ANY KEY TO CONTINUE....";
    getch();
    cout << "\n\n\t\t\t\t  ====VACCINE MANAGEMENT SYSTEM====  \n\n"
         << endl;
    cout << "\n\t\t\t\t*****************************************\n";
    cout << "\t\t\t\t\t\t  MENU";
    cout << "\n\t\t\t\t*****************************************\n";
    cout << "\n\t\t1: Search Vaccination center  \t\t\t 2: Add New Patient Data" << endl;
    cout << "\n\t\t3: Search Patient Data \t\t\t\t 4: Update Patient Dose" << endl;
    cout << "\n\t\t5: Add New Vaccine Stock   \t\t\t 6: Display Vaccine Stock" << endl;
    cout << "\n\t\t7: Show Total Number of vaccines applied \t 8: Add new nurse data  " << endl;
    cout << "\n\t\t9: Search and Display Nurse Data \t\t10: Exit";
}

int password()
{
    char u_name[20];
    char hide_name[20];
    int ch, i = 0, capt = 0, capta = 0;
    cout << "\n\n\t\tUSER NAME :- ";
    fflush(stdin);
    gets(u_name);
    cout << "\n\n\t\tPASSWORD  :- ";
    while ((ch = getch()) != 13)
    {
        cout << "*";
        hide_name[i] = ch;
        i++;
    }
    hide_name[i] = '\0';
    srand(time(0));
    capt = rand();
    cout << "\n\t\tCAPTA :-> " << capt;
    cout << "\n\tPlease Enter the valid Capta :-> ";
    cin >> capta;
    if ((strcmp(u_name, "vaccine") == 0) && (strcmp(hide_name, "aca") == 0) && (capt == capta))
        return 1;
    else
        return 0;
}
