/**********************
                   HEADER FILE USED IN PROJECT
***********************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>

using namespace std;

/**********************
                     CLASSES USED IN PROJECT
***********************/
class Login;
class Owner;
class Employee;
class Store;
class Order;
class Feedback;
class Bill;
//1)
class Login
{
protected:
    char User_ID[50];
    char Password[50];
    char Account_Type[10];
    bool OutOfLogin = false;
public:
    int Count = 0;
    int Login_Limit = 3;
    Login() : User_ID(), Password(), Account_Type("LOGIN") {}
    //VIRTUAL FUNCTION TO OVERRIDE BASE CLASS MEMBER FUNCTION
    virtual char* Get_AccType()
    {
        return Account_Type;
    }
    void Set_UserID()
    {
        cin.getline(User_ID, 50);
    }
    void Set_Password()
    {
        cin.getline(Password, 50);
    }
    void Set_OutOfLogin(bool OutofLogin)
    {
        this->OutOfLogin = OutofLogin;
    }
    char* Get_UserID()
    {
        return User_ID;
    }
    char* Get_Password()
    {
        return Password;
    }
    bool Get_OutOfLogin()
    {
        return OutOfLogin;
    }
};

//2)
class Owner : public Login
{
protected:
    char Account_Type[10];
public:
    Owner() : Account_Type("OWNER") {}
    char* Get_AccType() override
    {
        return Account_Type;
    }
    void Owner_Login();
};
void Owner::Owner_Login()
{
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
    cout << "\n\n\t|ENTER LOGIN ID| ";
    cin.ignore();
    Set_UserID();
    cout << "\n\n\t|ENTER LOGIN PASSWORD| ";
    Set_Password();
    while ((strcmp("Owner", Get_UserID()) != 0 || strcmp("1234", Get_Password()) != 0) && !Get_OutOfLogin())
    {
        system("cls");
        if (Count < Login_Limit)
        {
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cerr << "\n\n\tUSER NAME OR PASSWORD IS INCORRECT \n\n\tPLEASE RE-ENTER";
            cout << "\n\n\t|ENTER LOGIN ID| ";
            Set_UserID();
            cout << "\n\n\t|ENTER LOGIN PASSWORD| ";
            Set_Password();
            Count++;
        }
        else
        {
            Set_OutOfLogin(true);
        }
    }
    if (Get_OutOfLogin())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\t" << Count + 1 << " INCORRECT ATTEMPTS TO VERIFY LOGIN. TRY AGAIN LATER\n";
    }
    else
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cout << "\n\n\tLOGIN SUCCESSFUL!";
    }
}

//3)
class Store
{
private:
    char Item_Name[20];
    int Item_Price{};
    int Item_Qty{};
public:
    int Num_Items = 0;
    Store() : Item_Name(), Item_Price(), Item_Qty(), Num_Items() {}
    void Get_Item()
    {
        cout << "\n\n\tENTER ITEM NAME: ";
        cin.ignore();
        cin.getline(Item_Name, 20);
        cout << "\n\n\tENTER ITEM PRICE: ";
        cin >> Item_Price;
        cout << "\n\n\tENTER ITEM QUANTITY: ";
        cin >> Item_Qty;
    }
    void Show_Item()
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n\n";
        cout << "==========================================================\n";
        cout << "ITEM NAME                ITEMPRICE                ITEM QTY" << endl;
        cout << "==========================================================\n";
        cout << Item_Name << setw(18) << Item_Price << setw(20) << Item_Qty << endl;
    }
    char* Get_ItemName()
    {
        return Item_Name;
    }
    int Get_ItemPrice()
    {
        return Item_Price;
    }
    void Manage_Inventory();
    void View_Inventory();
};
void Store::Manage_Inventory()
{
    Store S;
    char Item_name[20];
    char ch;
    do
    {
        system("cls");
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cout << "\n\n\ta. ADD ITEM \n\n\tb. SEARCH ITEM \n\n\tc. MODIFY ITEM \n\n\td. DELETE ITEM \n\n\te. BACK";
        cout << "\n\n\tPlease Select Your Option (a-e) ";
        cin >> ch;
        switch (ch)
        {
        case 'a':
        case 'A':
        {
            system("cls");
            fstream Add_SFile("Canteen_Store.dat", ios::out | ios::binary | ios::app);
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\tENTER TOTAL NUMBER OF ITEMS YOU WANT TO ADD ";
            cin >> Num_Items;
            for (int i = 0; i < Num_Items; i++)
            {
                system("cls");
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cout << "\n\n\tITEM NO." << i + 1 << endl;
                S.Get_Item();
                Add_SFile.write(reinterpret_cast<char*>(&S), sizeof(Store));
            }
            Add_SFile.close();
            system("cls");
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\tITEM ADDED TO THE STORE INVENTORY";
            cout << "\n\n\tPRESS ANY KEY...";
            cin.ignore();
            cin.get();
        }
        break;
        case 'b':
        case 'B':
        {
            system("cls");
            fstream Search_SFile("Canteen_Store.dat", ios::in | ios::binary);
            if (Search_SFile.fail())
            {
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
                cin.ignore();
                cin.get();
                return;
            }
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\tENTER NAME OF ITEM YOU WANT TO SEARCH ";
            cin.ignore();
            cin.getline(Item_name, 20);
            bool search = false;
            system("cls");
            while (Search_SFile.read(reinterpret_cast<char*>(&S), sizeof(Store)))
            {
                if (strcmp(Item_name, S.Item_Name) == 0)
                {
                    S.Show_Item();
                    search = true;
                }
            }
            Search_SFile.close();
            if (search == false)
            {
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cerr << "\n\n\tITEM DOES NOT EXIST!";
            }
            cout << "\n\n\tPRESS ANY KEY...";
            cin.ignore();
        }
        break;
        case 'c':
        case 'C':
        {
            system("cls");
            fstream Modify_SFile("Canteen_Store.dat", ios::in | ios::out | ios::binary);
            if (Modify_SFile.fail())
            {
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
                cin.ignore();
                cin.get();
                return;
            }
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\tENTER NAME OF ITEM YOU WANT TO MODIFY ";
            cin.ignore();
            cin.getline(Item_name, 20);
            bool modify = false;
            system("cls");
            while (!Modify_SFile.eof() && modify == false)
            {
                Modify_SFile.read(reinterpret_cast<char*>(&S), sizeof(Store));
                if (strcmp(Item_name, S.Item_Name) == 0)
                {
                    S.Show_Item();
                    cout << "\n\n\tENTER NEW DETAILS OF ITEM\n";
                    S.Get_Item();
                    int pos = (-1) * static_cast<int>(sizeof(S));
                    Modify_SFile.seekp(pos, ios::cur);
                    Modify_SFile.write(reinterpret_cast<char*>(&S), sizeof(Store));
                    modify = true;
                }
            }
            Modify_SFile.close();
            if (modify == false)
            {
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cerr << "\n\n\tITEM DOES NOT EXIST!";
            }
            else
            {
                system("cls");
                cin.ignore();
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cout << "\n\n\tITEM UPDATED!";
            }
            cout << "\n\n\tPRESS ANY KEY...";
            cin.ignore();
        }
        break;
        case 'd':
        case 'D':
        {
            system("cls");
            fstream Delete_SFile("Canteen_Store.dat", ios::in | ios::binary);
            if (Delete_SFile.fail())
            {
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...\n";
                cin.ignore();
                cin.get();
                return;
            }
            fstream New_File("Temp_S.dat", ios::out | ios::binary);
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\tENTER NAME OF ITEM YOU WANT TO DELETE ";
            cin.ignore();
            cin.getline(Item_name, 20);
            Delete_SFile.seekg(0, ios::beg);
            while (Delete_SFile.read(reinterpret_cast<char*>(&S), sizeof(Store)))
            {
                if (strcmp(Item_name, S.Item_Name) != 0)
                {
                    New_File.write(reinterpret_cast<char*>(&S), sizeof(Store));
                }
            }
            Delete_SFile.close();
            New_File.close();
            //REMOVING OLD FILE
            if (remove("Canteen_Store.dat") != 0)
            {
                perror("\n\n\tREMOVE FAILED!");
            }
            //RENAMING NEW FILE
            if (rename("Temp_S.dat", "Canteen_Store.dat") != 0)
            {
                perror("\n\n\tRENAME FAILED!");
            }
            system("cls");
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\tITEM DELETED";
            cout << "\n\n\tPRESS ANY KEY...";
            cin.ignore();
        }
        break;
        case 'e':
        case 'E':
            break;
        }
    } while ((ch != 'e') && (ch != 'E'));
}
void Store::View_Inventory()
{
    system("cls");
    Store S;
    fstream View_SInvt("Canteen_Store.dat", ios::in | ios::binary);
    bool SInvt = false;
    if (View_SInvt.fail())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...\n";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n\n";
    cout << "======================================================\n";
    cout << "ITEM NAME              ITEMPRICE              ITEM QTY" << endl;
    cout << "======================================================\n";
    while (View_SInvt.read(reinterpret_cast<char*>(&S), sizeof(Store)))
    {
        cout << S.Item_Name << "\t\t " << S.Item_Price << "\t\t\t" << S.Item_Qty << endl << endl;
        SInvt = true;
    }
    View_SInvt.close();
    if (SInvt == false)
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tNO ITEM TO DISPLAY";
    }
    cout << "\n\n\tPRESS ANY KEY...";
    cin.ignore();
    cin.get();
}

//4)
class Employee : public Login
{
protected:
    char Account_Type[10]{};
private:
    int Emp_ID{};
    char Emp_Name[30]{};
    double Emp_Sal{};
    char Emp_Gender[10]{};
    int Emp_Age{};
    char Emp_Address[100]{};
public:
    //AGGREGATION RELATIONSHIP B/W EMPLOYEE & STORE
    Store* Emp_Store;
    Employee() : Emp_ID(), Emp_Name(), Emp_Gender(), Emp_Sal(), Emp_Age(), Emp_Address(), Account_Type("EMPLOYEE") {}
    Employee(Store* emp_store)
    {
        Emp_Store = new Store();
        this->Emp_Store = emp_store;
    }
    char* Get_AccType() override
    {
        return Account_Type;
    }
    void Get_Data()
    {
        cout << "\n\n\tENTER THE FOLLOWING \n\n\tEMPLOYEE ID \n\n\tEMPLOYEE NAME \n\n\tEMPLOYEE SALARY \n\n\tEMPLOYEE GENDER \n\n\tEMPLOYEE AGE \n\n\tEMPLOYEE ADDRESS\n";
        cout << "\n\n\tPRESS ANY KEY...";
        cin.ignore();
        cin.get();
        system("cls");
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cout << "\n\n\tENTER ID: ";
        cin >> Emp_ID;
        cout << "\n\n\tENTER NAME: ";
        cin.ignore();
        cin.getline(Emp_Name, 30);
        cout << "\n\n\tENTER SALARY: ";
        cin >> Emp_Sal;
        cout << "\n\n\tENTER GENDER: ";
        cin.ignore();
        cin.getline(Emp_Gender, 10);
        cout << "\n\n\tENTER AGE: ";
        cin >> Emp_Age;
        cout << "\n\n\tENTER ADDRESS: ";
        cin.ignore();
        cin.getline(Emp_Address, 100);
    }
    void Show_Data()
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n\n";
        cout << "======================================================================================================\n";
        cout << "EMP ID          EMP NAME          EMP SALARY          EMP GENDER          EMP AGE          EMP ADDRESS" << endl;
        cout << "======================================================================================================\n";
        cout << Emp_ID << setw(20) << Emp_Name << setw(18) << Emp_Sal << setw(20) << Emp_Gender << setw(18) << Emp_Age << setw(20) << Emp_Address << endl;
    }
    int Get_ID()
    {
        return Emp_ID;
    }
    void Employee_Login();
    void AddNew_Emp();
    template <typename Emp_Search>
    void Search_Emp(Emp_Search);
    template <typename Emp_Modify>
    void Modify_Emp(Emp_Modify);
    template <typename Emp_Delete>
    void Delete_Emp(Emp_Delete);
    void DisplayAll_Emp();
};
void Employee::Employee_Login()
{
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
    cout << "\n\n\t|ENTER LOGIN ID| ";
    cin.ignore();
    Set_UserID();
    cout << "\n\n\t|ENTER LOGIN PASSWORD| ";
    Set_Password();
    while ((strcmp("Employee", Get_UserID()) != 0 || strcmp("1234", Get_Password()) != 0) && !Get_OutOfLogin())
    {
        system("cls");
        if (Count < Login_Limit)
        {
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cerr << "\n\n\tUSER NAME OR PASSWORD IS INCORRECT \n\n\tPLEASE RE-ENTER";
            cout << "\n\n\t|ENTER LOGIN ID| ";
            Set_UserID();
            cout << "\n\n\t|ENTER LOGIN PASSWORD| ";
            Set_Password();
            Count++;
        }
        else
        {
            Set_OutOfLogin(true);
        }
    }
    if (Get_OutOfLogin())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\t" << Count + 1 << " INCORRECT ATTEMPTS TO VERIFY LOGIN. TRY AGAIN LATER\n";
    }
    else
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cout << "\n\n\tLOGIN SUCCESSFUL!";
    }
}
void Employee::AddNew_Emp()
{
    system("cls");
    Employee E;
    ofstream Emp_File("Emp_Data.dat", ios::binary | ios::app);
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n\n";
    E.Get_Data();
    Emp_File.write(reinterpret_cast<char*>(&E), sizeof(Employee));
    Emp_File.close();
    system("cls");
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
    cout << "\n\n\tEMPLOYEE ADDED";
    cout << "\n\n\tPRESS ANY KEY...";
    cin.ignore();
}
template <typename Emp_Search>
void Employee::Search_Emp(Emp_Search ID)
{
    system("cls");
    Employee E;
    ifstream Search_EFile("Emp_Data.dat", ios::binary);
    if (Search_EFile.fail())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
        cin.ignore();
        cin.get();
        return;
    }
    bool Search = false;
    while (Search_EFile.read(reinterpret_cast<char*>(&E), sizeof(Employee)))
    {
        if (ID == E.Get_ID())
        {
            E.Show_Data();
            Search = true;
        }
    }
    Search_EFile.close();
    if (Search == false)
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tRECORD NOT EXIST!";
    }
    cout << "\n\n\tPRESS ANY KEY...";
    cin.ignore();
    cin.get();
}
template <typename Emp_Modify>
void Employee::Modify_Emp(Emp_Modify ID)
{
    system("cls");
    Employee E;
    bool Modify = false;
    fstream Modify_EFile("Emp_Data.dat", ios::binary | ios::in | ios::out);
    if (Modify_EFile.fail())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!Modify_EFile.eof() && Modify == false)
    {
        Modify_EFile.read(reinterpret_cast<char*>(&E), sizeof(Employee));
        if (ID == E.Get_ID())
        {
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n\n";
            E.Show_Data();
            cout << "\n\n\tPLEASE ENTER THE NEW DETIALS OF EMPLOYEE\n";
            E.Get_Data();
            int pos = (-1) * static_cast<int>(sizeof(E));
            Modify_EFile.seekp(pos, ios::cur);
            Modify_EFile.write(reinterpret_cast<char*>(&E), sizeof(Employee));
            Modify = true;
        }
    }
    Modify_EFile.close();
    if (Modify == false)
    {
        cin.ignore();
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tRECORD NOT FOUND!";
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cout << "\n\n\tRECORD UPDATED!";
    }
    cout << "\n\n\tPRESS ANY KEY...";
    cin.ignore();
}
template <typename Emp_Delete>
void Employee::Delete_Emp(Emp_Delete ID)
{
    system("cls");
    Employee E;
    ifstream Delete_EFile("Emp_Data.dat", ios::binary);
    if (Delete_EFile.fail())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream New("Temp_E.dat", ios::binary);
    Delete_EFile.seekg(0, ios::beg);
    while (Delete_EFile.read(reinterpret_cast<char*>(&E), sizeof(Employee)))
    {
        if (ID != E.Get_ID())
        {
            New.write(reinterpret_cast<char*>(&E), sizeof(Employee));
        }
    }
    Delete_EFile.close();
    New.close();
    //REMOVING OLD FILE
    if (remove("Emp_Data.dat") != 0)
    {
        perror("\n\n\tREMOVE FAILED!");
    }
    //RENAMING NEW FILE
    if (rename("Temp_E.dat", "Emp_Data.dat") != 0)
    {
        perror("\n\n\tRENAME FAILED!");
    }
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
    cout << "\n\n\tRECORD DELETED!";
    cout << "\n\n\tPRESS ANY KEY...";
    cin.ignore();
    cin.get();
}
void Employee::DisplayAll_Emp()
{
    system("cls");
    Employee E;
    fstream All_EFile("Emp_Data.dat", ios::in | ios::binary);
    bool All = false;
    if (All_EFile.fail())
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n\n";
    cout << "======================================================================================================\n";
    cout << "EMP ID          EMP NAME          EMP SALARY          EMP GENDER          EMP AGE          EMP ADDRESS" << endl;
    cout << "======================================================================================================\n";
    while (All_EFile.read(reinterpret_cast<char*>(&E), sizeof(Employee)))
    {
        cout << E.Emp_ID << setw(20) << E.Emp_Name << setw(18) << E.Emp_Sal << setw(20) << E.Emp_Gender << setw(18) << E.Emp_Age << setw(24) << E.Emp_Address << endl;
        All = true;
    }
    All_EFile.close();
    if (All == false)
    {
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cerr << "\n\n\tNO EMPLOYEE TO DISPLAY";
    }
    cout << "\n\n\tPRESS ANY KEY...";
    cin.ignore();
    cin.get();
}
//PRINT FUNCTION TO PRINT ACCOUNT TYPE
void Print_AccType(Login* _Login)
{
    cout << "\n\n\tACCOUNT TYPE: " << _Login->Get_AccType() << endl;
}

//5)
class Bill
{
public:
    char Customer_Name[30]{};
    double Amount{};
    Bill() : Customer_Name() {}
    char* Get_CustomerName()
    {
        return Customer_Name;
    }
    void Total_Bill();
};
void Bill::Total_Bill()
{
    system("cls");
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
    cout << "\n\n\tENTER NAME OF THE CUSTOMER ";
    cin.ignore();
    cin.getline(Customer_Name, 30);
}

//6)
class Order
{
private:
    char ItemName[20]{};
    int ItemPrice{};
    int ItemQty{};
public:
    //COMPSITION RELATIONSHIP B/W ORDER & BILL
    Bill Order_Bill;
    bool Biryani = false;
    bool Shawarma = false;
    bool Coffee = false;
    Order() : ItemName(), ItemPrice(), ItemQty() {}
    Order(Bill order_bill)
    {
        this->Order_Bill = order_bill;
    }
    int Get_Price()
    {
        return ItemPrice;
    }
    void New_Order();
};
void Order::New_Order()
{
    Store Order_Store;
    int Count;
    int n = 0;
    char Choice;
    do
    {
        Count = 0;
        fstream OrderItem("Canteen_Store.dat", ios::in | ios::binary);
        if (OrderItem.fail())
        {
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cerr << "\n\n\tFILE COULD NOT BE OPEN !! PRESS ANY KEY...";
            cin.ignore();
            cin.get();
            return;
        }
        system("cls");
        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
        cout << "\n\n\tITEMS LIST\n";
        cout << "======================================================\n";
        cout << "ITEM NO.              ITEM NAME              ITEMPRICE" << endl;
        cout << "======================================================\n";
        while (OrderItem.read(reinterpret_cast<char*>(&Order_Store), sizeof(Store)))
        {
            cout << Count + 1 << setw(30) << Order_Store.Get_ItemName() << setw(20) << Order_Store.Get_ItemPrice() << endl;
            Count++;
        }
        cout << "\n\n\tPLEASE CHOOSE ANY\n";
        cout << "\n\n\tPlease Enter Your Option ";
        cin.ignore();
        cin.getline(ItemName, 20);
        while ((strcmp("CHICKEN BIRYANI", ItemName) != 0) && (strcmp("SHAWARMA", ItemName) != 0) && (strcmp("COFFEE", ItemName) != 0))
        {
            cout << "\n\n\tINVALID ITEM ENTERED!" << endl;
            cout << "\n\n\tPLEASE RE-ENTER ITEM OR PRESS 1 TO CANCEL ";
            cin.getline(ItemName, 20);
            if (strcmp("1", ItemName) == 0)
            {
                break;
            }
        }
        if (strcmp("CHICKEN BIRYANI", ItemName) == 0)
        {
            Biryani = true;
            cout << "\n\n\tPLEASE ENTER QUANTITY ";
            cin >> ItemQty;
            while (ItemQty > 35)
            {
                cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                cout << "\n\n\tPLEASE ENTER QUANTITY LESS THAN " << ItemQty << " ";
                cin >> ItemQty;
            }
            for (int i = 0; i < ItemQty; i++)
            {
                ItemPrice += 200;
            }
        }
        else if (strcmp("SHAWARMA", ItemName) == 0)
        {
            Shawarma = true;
            cout << "\n\n\tPLEASE ENTER QUANTITY ";
            cin >> ItemQty;
            while (ItemQty > 20)
            {
                cout << "\n\n\tPLEASE ENTER QUANTITY LESS THAN " << ItemQty << endl;
                cin >> ItemQty;
            }
            for (int i = 0; i < ItemQty; i++)
            {
                ItemPrice += 150;
            }
        }
        else if (strcmp("COFFEE", ItemName) == 0)
        {
            Coffee = true;
            cout << "\n\n\tPLEASE ENTER QUANTITY ";
            cin >> ItemQty;
            while (ItemQty > 25)
            {
                cout << "\n\n\tPLEASE ENTER QUANTITY LESS THAN " << ItemQty << endl;
                cin >> ItemQty;
            }
            for (int i = 0; i < ItemQty; i++)
            {
                ItemPrice += 400;
            }
        }
        OrderItem.close();
        cout << "\n\n\tDO YOU WANT TO CHOOSE ANY OTHER ITEM (YES/NO)? ";
        cin >> Choice;
    } while (Choice == 'y' || Choice == 'Y');
    system("cls");
    cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
    cout << "\n\n\tGENERATE CUSTOMER'S BILL (YES/NO?) ";
    cin >> Choice;
    system("cls");
    if (Choice == 'y' || Choice == 'Y')
    {
        Order_Bill.Amount = 0;
        Order_Bill.Total_Bill();
        if (Biryani == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        else if (Biryani == true && Shawarma == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        else if (Biryani == true && Coffee == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        else if (Biryani == true && Shawarma == true && Coffee == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        else if (Shawarma == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        else if (Shawarma == true && Coffee == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        else if (Coffee == true)
        {
            Order_Bill.Amount = 0;
            Order_Bill.Amount += ItemPrice;
            cout << "\n\n\tBILL: " << "PAY FOLLOWING AMOUNT" << endl;
            cout << "\n\n\tCUSTOMER NAME: " << Order_Bill.Get_CustomerName() << endl;
            cout << "\n\n\tTOTAL AMOUNT: " << Order_Bill.Amount << endl;
        }
        cout << "\n\n\tTHANK YOU!";
        cout << "\n\n\tPRESS ANY KEY...\n";
    }
}
//7
class Feedback
{
private:
    string Name;
    string Mobile_No;
    string Email;
    string rating;
public:
    Feedback() : Name(), Mobile_No(), Email(), rating() {}
    //FRIEND FUNCTION DECLARATION
    friend void Service(Feedback);
};
void Service(Feedback obj)
{
    system("cls");
    char ch;
    cout << "\n\n\t=================================================================================================";
    cout << "\n\n\tDO YOU WANT TO SIGN UP FOR OUR SERVICE QUALITY INSPECTION & MONTHLY PRODUCT PROMOTIONS:) (YES/NO?)";
    cout << "\n\n\t================================================================================================= ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        cout << "\n\n\tPLEASE ENTER YOUR CONTACT DETAILS" << endl;
        cout << "\n\n\tYOUR NAME: ";
        cin.ignore();
        getline(cin, obj.Name);
        cout << "\n\n\tYOUR MOBILE NUMBER: ";
        cin >> obj.Mobile_No;
        cout << "\n\n\tYOUR EMAIL ADDRESS: ";
        cin >> obj.Email;
    }
    else
    {
        cout << "\n\n\tNO WORRIES SIR!" << endl;
    }
    system("cls");
    cout << "\n\n\tPLEASE SELECT BETWEEN THE OPTIONS ABOUT OUR SERVICE" << endl;
    cout << "\n\n\tGOOD :)";
    cout << "\n\n\tNEUTRAL :|";
    cout << "\n\n\tBAD :(\n";
    cin >> obj.rating;
}
void intro()
{
    cout << "\n\n\n\t\tAIR UNIVERSITY CANTEEN";
    cout << "\n\n\t\tMANAGEMENT SYSTEM";
    cout << "\n\n\t\t     PROJECT";
    cout << "\n\tAIR UNIVERSITY, ISLAMABAD\n";
    cin.get();
}
int main()
{
    intro();
    system("cls");
    //BASE CLASS POINTER POINTING TO DERIVED CLASS OBJECT
    Login* Owner_Acc = new Owner();
    Login* Emp_Acc = new Employee();
    Owner _Owner;
    //AGGREGATION
    Store* _Store = new Store();
    Employee* _Emp = new Employee(_Store);
    Bill _Bill;
    //COMPOSITION
    Order* _Order = new Order(_Bill);
    Feedback Obj;
    char ch;
    int n;
    int ID;
    do
    {
        system("cls");
        cout << "\t\t\t\t~~~~~~~~\n\t\t\t\tWELCOME TO AIR UNIVERSITY CANTEEN\n\t\t\t\t~~~~~~~~";
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. LOGIN";
        cout << "\n\n\t02. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-2) ";
        cin >> ch;
        if (ch == '1')
        {
            system("cls");
            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
            cout << "\n\n\t1. OWNER LOGIN \n\n\t2. EMPLOYEE LOGIN \n\n\t3. EXIT";
            cout << "\n\n\tPlease Select Your Option (1-3) ";
            cin >> n;
            if (n == 1)
            {
                system("cls");
                _Owner.Owner_Login();
                if (_Owner.Get_OutOfLogin() == false)
                {
                    do
                    {
                        system("cls");
                        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                        Print_AccType(Owner_Acc);
                        cout << "\n\n\t1. ADD EMPLOYEE \n\n\t2. SEARCH EMPLOYEE \n\n\t3. MODIFY EMPLOYEE \n\n\t4. DELETE EMPLOYEE \n\n\t5. DISPLAY ALL EMPLOYEE \n\n\t6. LOGOUT";
                        cout << "\n\n\tPlease Select Your Option (1-6) ";
                        cin >> n;
                        if (n == 1)
                        {
                            _Emp->AddNew_Emp();
                        }
                        else if (n == 2)
                        {
                            system("cls");
                            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                            cout << "\n\n\tENTER ID OF THE EMPLOYEE YOU WANT TO SEARCH ";
                            cin >> ID;
                            _Emp->Search_Emp(ID);

                        }
                        else if (n == 3)
                        {
                            system("cls");
                            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                            cout << "\n\n\tENTER ID OF THE EMPLOYEE YOU WANT TO MODIFY ";
                            cin >> ID;
                            _Emp->Modify_Emp(ID);
                        }
                        else if (n == 4)
                        {
                            system("cls");
                            cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                            cout << "\n\n\tENTER ID OF THE EMPLOYEE YOU WANT TO DELETE ";
                            cin >> ID;
                            _Emp->Delete_Emp(ID);
                        }
                        else if (n == 5)
                        {
                            _Emp->DisplayAll_Emp();
                        }
                        else if (n == 6)
                        {
                            break;
                        }
                    } while (n != 6);
                }
                else
                {
                    cout << "\n\n\tLOGIN FAILED !! PRESS ANY KEY...";
                    cin.ignore();
                }
            }
            else if (n == 2)
            {
                system("cls");
                _Emp->Employee_Login();
                if (_Emp->Get_OutOfLogin() == false)
                {
                    do
                    {
                        system("cls");
                        cout << "\n\t\t\t\tAIR UNIVERSITY CANTEEN\n\n";
                        Print_AccType(Emp_Acc);
                        cout << "\n\n\t1. MANAGE INVENTORY \n\n\t2. VIEW INVENTORY \n\n\t3. NEW ORDER \n\n\t5. LOGOUT";
                        cout << "\n\n\tPlease Select Your Option (1-4) ";
                        cin >> n;
                        if (n == 1)
                        {
                            _Emp->Emp_Store->Manage_Inventory();
                        }
                        else if (n == 2)
                        {
                            _Emp->Emp_Store->View_Inventory();
                        }
                        else if (n == 3)
                        {
                            _Order->New_Order();
                            cin.ignore();
                            Service(Obj);

                            
                        }
                        else if (n == 4)
                        {
                            break;
                        }
                    } while (n != 4);
                }
                else
                {
                    cout << "\n\n\tLOGIN FAILED !! PRESS ANY KEY...";
                    cin.ignore();
                }
            }
        }
        else if (ch == '2')
        {
            break;
        }
    } while (ch != '2');
    delete _Emp;
    delete _Order;

    cout << "\n\aPROGRAM ENDED...";
    return 0;
}
