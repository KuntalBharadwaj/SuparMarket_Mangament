#include <iostream>
#include <fstream>

using namespace std;

class shopping {
    private: 
        int pcode;
        float price, dis;
        string pname;

    public: 
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void shopping::menu() {
    m:

    int choice;
    string email;
    string password;

    cout << "\t\t\t\t___________________________\n";
    cout << "\t\t\t\t                           \n";
    cout << "\t\t\t\t   Supermarket Main Menu   \n";
    cout << "\t\t\t\t                           \n";
    cout << "\t\t\t\t___________________________\n\n";
    cout << "\t\t\t\t     1)Administrator       |\n";
    cout << "\t\t\t\t                          |\n";    
    cout << "\t\t\t\t         2)Buyer          |\n";
    cout << "\t\t\t\t                          |\n";
    cout << "\t\t\t\t         3)Exit           |\n";
    cout << "\t\t\t\t                          |\n";
    cout << "\t\t\t\t      Please Select!      |\n";
    cin >> choice;

    switch(choice)
    {
        case 1: {
            cout << "\t\t\t Please login \n";
            cout << "\t\t\t Enter Email   \n";
            cin >> email;
            cout << "\t\t\t Enter Password   \n";
            cin >> password;

            if(email == "admin@email.com" && password == "admin@123") {
                administrator();
            }
            else {
                cout << "Invalid email/password";
            }
            break;
        }

        case 2: {
            buyer();
            break;
        }

        case 3: 
            exit(0);

        default: 
            cout << "Please Select from the given option!";
    }

    goto m;
}

void shopping::administrator() {
    m:
    int choice;
    cout << "\n\n\t\n\t\t\t |       Administrator Menu      |\t\t\t\n";
    cout << "\n\t\t\t\t\t\t\t______1) Add the product_________|\n";
    cout << "\n\t\t\t\t\t\t\t______2) Modify the product______|\n";
    cout << "\n\t\t\t\t\t\t\t______3) Delete the product______|\n";
    cout << "\n\t\t\t\t\t\t\t______4) Go Back_________|\n";

    cout << "Please Enter your Choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            add();
            break;
        
        case 2:
            edit();
            break;
        
        case 3:
            rem();
            break;

        case 4:
            menu();
            break;

        default: 
            cout << "Invalid choice";
    }
    goto m;
}

void shopping::buyer() {
    m:
    int choice;
    cout << "\n\n\t\n\t\t\t|               Buyer Menu              |\t\t\t\n";
    cout << "\n\t\t\t\t\t\t\t______1) Buy product_________|\n";
    cout << "\n\t\t\t\t\t\t\t______2) Go Back_________|\n";

    cout << "Please Enter your Choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            receipt();
            break;
        
        case 2:
            menu();
            break;

        default: 
            cout << "Invalid choice";
    }
    goto m;
}

void shopping::add() {
    m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\n\t\t\t|        Add new product           |\t\t\t\n";
    cout << "\n\t\t\t\t\t\t\t______Product code of the product_________|\n";
    cin >> pcode;

    cout << "\n\t\t\t\t\t\t\t______Name of the product______|\n";
    cin >> pname;

    cout << "\n\t\t\t\t\t\t\t______Price of the product______|\n";
    cin >> price;

    cout << "\n\t\t\t\t\t\t\t______Discount on the product______|\n";
    cin >> dis;
    
    data.open("database.txt", ios::in);

    if(!data) {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else {
        data >> c >> n >> p >> d;

        while(!data.eof()) {
            if(c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if(token == 1) goto m;
        else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
        cout << "\t\t\t\t_____Record Inserted_____\t\t\t\t\n";
    }
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t______Modify the record______\t\t\t\t\n";
    cout << "\n\t\t\t______Product Code______\t\t\t\t\n";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if(!data) cout << "\n\n\t\t______File doesn't exist!______\t\t\t\n";
    
    else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while(!data.eof()) {
            if(pkey == pcode) {
                cout << "\n\n\t\t______Product New Code______\t\t\t\n";
                cin >> c;
                cout << "\n\n\t\t______Name of the Product______\t\t\t\n";
                cin >> n;
                cout << "\n\n\t\t______Price______\t\t\t\n";
                cin >> p;
                cout << "\n\n\t\t______Discount______\t\t\t\n";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t______Record edited______\t\t\t\n";
                token++;
            }
            else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0) cout << "\n\n\t\t\t______Record not found sorry!______\t\t\t\n";
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\t\t\t______Delete record______\t\t\t\t\n";
    cout << "\n\t\t\t______Product Code______\t\t\t\t\n";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if(!data) cout << "\n\n\t\t______File doesn't exist!______\t\t\t\n";
    
    else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        
        while(!data.eof()) {
            if(pkey == pcode) {
                cout << "\n\n\t\t______Product Deleted Successfully!______\t\t\t\n";
                token++;
            }
            else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0) cout << "\n\n\t\t\t______Record not found sorry!______\t\t\t\n";
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n___________________________|\n";
    cout << "Product No \t\tName \t\tPrice\n";
    cout << "\n\n|___________________________|\n";
    data >> pcode >> pname >> price >> dis;

    while(!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt() {
    m:
    fstream data;

    int arrc[100];
    int arrq[100];

    char choice;
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t Receipt \t\t\n";
    data.open("database.txt", ios::in);

    if(!data) {
        cout << "\n\n Empty database";
    }
    else {
        data.close();
        list();
        cout << "\n_________________________________\n";
        cout << "\n                                 \n";
        cout << "\n______ Please Place the Order____\n";
        cout << "\n                                 \n";
        cout << "\n_________________________________\n";

        do {
            cout << "\n\nEnter Product code: ";
            cin >> arrc[c];
            cout << "\n\nEnter the Product quantity: ";
            cin >> arrq[c];

            for(int i = 0; i < c; i++) {
                if(arrc[c] == arrc[i]) {
                    cout << "\nDuplicate Product code. Please try again";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Do you want to buy another product? If yes, then press y else no: ";
            cin >> choice;
        } while(choice == 'y' || choice == 'Y');

        cout << "\n\n\t\t\t______________________RECEIPT_________________\n";
        cout << "\nProduct No\t Product Name\t Product Quantity \tPrice \tAmount with Discount\n";

        for(int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;

            while(!data.eof()) {
                if(pcode == arrc[i]) {
                    amount = price * arrq[i];
                    discount = amount - (amount * dis / 100);
                    total += discount;
                    cout << "\n" << pcode << "\t" << pname << "\t" << arrq[i] << "\t" << price << "\t" << amount << "\t" << discount;
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
    }
    cout << "\n\n_____________________________________";
    cout << "\n Total Amount: " << total;
}

int main() {
    shopping s;
    s.menu();
    
    return 0;
}
