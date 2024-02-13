#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Node
{
public:
    int data;
    double price;
    string foodname;
    int quantity;
    Node *next;
    Node *prev;
};

class Restaurant
{
private:
    Node *newnode;
    Node *head_cus;
    Node *tail_cus;
    Node *head_adm;
    Node *tail_adm;
    Node *head_sale;
    int id;
    string password;

public:
    Restaurant()
    {
        head_cus = tail_cus = nullptr;
        head_adm = tail_adm = nullptr;
        head_sale = nullptr;
        id = 12015786;
        password = "Shyam@123";
    }

    // CUSTOMER MENU
    void customermenu()
    {
        cout << "\t\t\t\t\t\t\t1. Place your order" << endl;
        cout << "\t\t\t\t\t\t\t2. View your ordered items" << endl;
        cout << "\t\t\t\t\t\t\t3. Delete an item from order" << endl;
        cout << "\t\t\t\t\t\t\t4. Display final bill" << endl;
        cout << "\t\t\t\t\t\t\t5. Back To Main Menu" << endl;
        cout << endl
             << "\t\t\t\t\t\t\tEnter Your Choice: -->";
    }

    // CREATE ITEM
    Node *CreateItem(Node *head, int data, int quantity)
    {
        newnode = new Node();
        Node *temp1 = head_adm;
        int flag = 0;

        while (temp1 != nullptr)
        {
            if (temp1->data == data)
            {
                flag = 1;
                break;
            }
            temp1 = temp1->next;
        }

        if (flag == 1)
        {
            newnode->data = data;
            newnode->price = quantity * (temp1->price);
            newnode->quantity = quantity;
            newnode->foodname = temp1->foodname;
            newnode->next = nullptr;
            newnode->prev = nullptr;

            Node *temp = head;

            if (temp == nullptr)
                head_cus = tail_cus = newnode;
            else
            {
                while (temp->next != nullptr)
                    temp = temp->next;

                temp->next = newnode;
                newnode->prev = tail_cus;
                tail_cus = newnode;
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tThis item is not present in the menu!" << endl;
        }
        return head_cus;
    }

    // TOTAL SALE
    Node *totalsales(int data, int quantity)
    {
        newnode = new Node();
        int flag = 0;

        Node *temp1 = head_adm;
        while (temp1->data != data)
        {
            temp1 = temp1->next;
        }

        newnode->data = data;
        newnode->price = quantity * (temp1->price);
        newnode->quantity = quantity;
        newnode->foodname = temp1->foodname;
        newnode->next = nullptr;
        newnode->prev = nullptr;

        Node *temp = head_sale;

        if (temp == nullptr)
            head_sale = newnode;
        else
        {
            while (temp->next != nullptr)
            {
                if (temp->data == data)
                {
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }

            if (flag == 1)
            {
                temp->quantity += newnode->quantity;
                temp->price += newnode->price;
            }
            else
            {
                temp->next = newnode;
            }
        }

        return head_sale;
    }

    // CALCULATE TOTAL SALE
    void calculateTotalSales()
    {
        Node *temp = head_cus;
        while (temp != nullptr)
        {
            head_sale = totalsales(temp->data, temp->quantity);
            temp = temp->next;
        }
    }

    // DELETE ITEM
    bool deleteItem()
    {
        cout << "\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
        int num1;
        cin >> num1;

        cout << "\t\t\t\t\tFor reducing the quantity only type 1 and for Deleting the whole item type 2: ";
        int num2;
        cin >> num2;

        Node *temp = head_cus;
        if (num2 == 2)
        {
            while (temp != nullptr)
            {
                if (temp->data == num1)
                {
                    head_cus = Delete(num1, head_cus, tail_cus);
                    return true;
                }
                temp = temp->next;
            }
        }
        else
        {
            while (temp != nullptr)
            {
                if (temp->data == num1 && temp->quantity > 1)
                {
                    head_cus = DecreaseQuant(num1, head_cus, tail_cus);
                    return true;
                }
                temp = temp->next;
            }
        }

        return false;
    }

    // DISPLAY TOTAL BILL
    void displayBill()
    {
        displayList(head_cus);
        Node *temp = head_cus;
        double total_price = 0;
        while (temp != nullptr)
        {
            total_price += temp->price;
            temp = temp->next;
        }

        cout << "\t\t\t\t\t\t\tTotal price:" << total_price << endl;
    }

    // DELETE LIST OF PARTICULAR ORDER
    Node *deleteList(Node *head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
                temp->prev = nullptr;
            }
            // free(temp);
            delete temp;
            temp = nullptr;
            head = nullptr;
        }

        return head;
    }

    // CUSTOMER BAR
    void customer()
    {
        int flag = 0, j = 1;
        char ch;
        cout << "\t\t------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t    CUSTOMER SECTION" << endl;
        cout << "\t\t------------------------------------------------------------------------" << endl;
        while (true)
        {
            customermenu();

            int opt;
            cin >> opt;

            if (opt == 5)
                break;

            switch (opt)
            {
            case 1:
                displayList(head_adm);
                while (true)
                {
                    cout << "\t\t\t\t\t\tEnter number corresponding to the item you want to order and 0 to exit the Food menu: ";
                    int n;
                    cin >> n;
                    if (n == 0)
                    {
                        cout << "\t\t\t\t\t*Your order is complete!!*" << endl;
                        break;
                    }
                    cout << "\t\t\t\t\t\tEnter quantity: ";
                    int quantity;
                    cin >> quantity;
                    head_cus = CreateItem(head_cus, n, quantity);
                }
                break;
            case 2:
                cout << "\t\t\t\t\t\t\t  ### List of ordered items ###" << endl;
                displayList(head_cus);
                break;
            case 3:
                if (deleteItem())
                {
                    cout << "\t\t### Updated list of your ordered food items ###" << endl;
                    displayList(head_cus);
                }
                else
                    cout << "\t\tFood item with the given serial number doesn't exist!!" << endl;
                break;
            case 4:
                calculateTotalSales();
                cout << "\t\t\t\t\t\t\t  ### Final Bill ###" << endl;
                displayBill();
                head_cus = deleteList(head_cus);
                flag = 1;
                break;
            default:
                cout << "\t\t\t\t\t\tWrong Input !! Please choose a valid option" << endl;
                break;
            }
            if (flag == 1)
                break;
        }
    }

    // CREATE ADMIN
    Node *CreateAdmin(Node *head, int data, string foodname, double price)
    {
        newnode = new Node();
        newnode->data = data;
        newnode->price = price;
        newnode->quantity = 0;
        newnode->foodname = foodname;
        newnode->next = nullptr;
        newnode->prev = nullptr;

        Node *temp = head;
        if (temp == nullptr)
            head_adm = tail_adm = newnode;
        else
        {
            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tail_adm;
            tail_adm = newnode;
        }
        return head_adm;
    }

    // ADMIN MENU
    void AdminMenu()
    {
        cout << "\t\t\t1. View total sales" << endl;
        cout << "\t\t\t2. Add new items in the order menu" << endl;
        cout << "\t\t\t3. Delete items from the order menu" << endl;
        cout << "\t\t\t4. Display order menu" << endl;
        cout << "\t\t\t5. Back To MainScreen" << endl;
        cout << endl
             << "\t\t\t\t\tEnter Your Choice: -->";
    }

    // DELETE WHOLE DATA
    Node *Delete(int data, Node *head, Node *tail)
    {
        if (head == nullptr)
        {
            cout << "\t\t\t\t\t\t\tList is empty" << endl;
        }
        else
        {
            Node *temp;
            if (data == head->data)
            {
                temp = head;
                head = head->next;
                if (head != nullptr)
                    head->prev = nullptr;
            }
            else if (data == tail->data)
            {
                temp = tail;
                tail = tail->prev;
                tail->next = nullptr;
            }
            else
            {
                temp = head;
                while (data != temp->data)
                {
                    temp = temp->next;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
        }

        return head;
    }

    // DECREASING QUANTITY OF ITEM
    Node *DecreaseQuant(int data, Node *head, Node *tail)
    {
        if (head == nullptr)
        {
            cout << "\t\t\t\t\t\t\tList is empty" << endl;
        }
        else
        {
            Node *temp;
            if (data == head->data)
            {
                temp = head;
                head->quantity = head->quantity - 1;
                if (head != nullptr)
                {
                    head->prev = nullptr;
                }
            }
            else if (data == tail->data)
            {
                temp = tail;
                tail->quantity = tail->quantity - 1;
            }
            else
            {
                temp = head;
                while (data != temp->data)
                {
                    temp = temp->next;
                }
                temp->quantity = temp->quantity - 1;
            }
        }

        return head;
    }

    // FUNCTION TO DELETE ITEMS
    bool DeleteAdmin()
    {
        cout << "\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
        int num;
        cin >> num;

        Node *temp = head_adm;
        while (temp != nullptr)
        {
            if (temp->data == num)
            {
                head_adm = Delete(num, head_adm, tail_adm);
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    // TO DISPLAY TOTAL SALE IN DAY
    void displayList(Node *head)
    {
        Node *temp1 = head;
        if (temp1 == nullptr)
        {
            cout << "\t\t\t\t\t\t\t\tList is empty!!" << endl;
        }
        else
        {
            while (temp1 != nullptr)
            {
                if (temp1->quantity == 0)
                    cout << "\t\t\t\t\t\t" << temp1->data << "."
                         << " " << temp1->foodname << " " << temp1->price << endl;
                else
                {
                    cout << "\t\t\t\t\t\t" << temp1->data << "."
                         << " " << temp1->foodname << " " << temp1->quantity << " " << temp1->price << endl;
                }

                temp1 = temp1->next;
            }
        }
    }

    // ADMIN BAR
    void Admin()
    {
        cout << endl;
        cout << "\t\t-------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\tADMIN SECTION" << endl;
        cout << "\t\t-------------------------------------------------------------------------" << endl;
        while (true)
        {
            AdminMenu(); // prints admin functionality list
            int option;
            cin >> option;
            if (option == 5)
            {
                break;
            }

            switch (option)
            {
            case 1:
                displayList(head_sale);
                break;
            case 2:
            {
                cout << "\t\t\t\t\t\t\tEnter serial no. of the food item:";
                int num;
                cin >> num;
                int flag = 0;
                string foodname;
                double price;
                Node *temp = head_adm;

                while (temp != nullptr)
                {
                    if (temp->data == num)
                    {
                        cout << "\t\t\t\t\t\tFood item with given serial number already exists!!" << endl;
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if (flag == 1)
                    break;

                cout << "\t\t\t\t\t\t\tEnter price: ";
                cin >> price;
                cout << "\t\t\t\t\t\t\tEnter food-item: ";
                cin >> foodname;
                head_adm = CreateAdmin(head_adm, num, foodname, price);
                cout << "\t\t\t\t\t\t\tSuccessfull! New food item added to the list!!" << endl;
                break;
            }
            case 3:
                if (DeleteAdmin())
                {
                    cout << "\t\t\t\t\t\t### Updated list of food items menu ###" << endl;
                    displayList(head_adm);
                }
                else
                    cout << "\t\t\t\t\t\tFood item with given serial number doesn't exist!" << endl;
                break;
            case 4:
                cout << "\t\t\t\t\t\t\t ### Order menu ###" << endl;
                displayList(head_adm);
                break;
            default:
                cout << "\t\t\t\t\t\tWrong Input !! Please choose a valid option" << endl;
                break;
            }
        }
    }

    // MAIN DISPLAY
    void MainScreen()
    {
        cout << "\t\t-------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\tWELCOME TO Yadav Ji Restaurant " << endl;
        cout << "\t\t-------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t1.ADMIN SECTION" << endl;
        cout << "\t\t\t\t2.CUSTOMER SECTION" << endl;
        cout << "\t\t\t\t3.EXIT" << endl;
        cout << endl
             << "\t\tEnter Your Choice: -->";
    }

    // MAIN FUNCTION
    void run()
    {
        Restaurant restaurant;
        head_adm = CreateAdmin(head_adm, 1, "Noodles", 120);
        head_adm = CreateAdmin(head_adm, 2, "Manchurian", 100);
        head_adm = CreateAdmin(head_adm, 3, "hot n sour Soup", 50);
        head_adm = CreateAdmin(head_adm, 4, "Cheese Burger", 60);
        head_adm = CreateAdmin(head_adm, 5, "Spring rolls", 80);
        bool flag = true;

        while (true)
        {
            MainScreen();
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cout << "\t\t\t\t\tEnter the id please:";
                int i_d;
                cin >> i_d;
                cout << "\t\t\t\t\tEnter the password please:";
                string pass;
                cin >> pass;
                if (i_d == id && pass == password)
                {
                    cout << "\t\t\t\t\t***Welcome to Admin section*" << endl;
                    Admin();
                }
                else
                {
                    cout << "\t\t\t\t\t***UNAUTHORIZED ACCESS*" << endl;
                }
                break;
            }
            case 2:
                customer();
                break;
            case 3:
                cout << "\t\t\t\t\t\t***Thank you for visiting!!***" << endl;
                flag = false;
                break;
            default:
                cout << "\t\t\t\t\t\tWrong Input !! Please choose a valid option" << endl;
                break;
            }
            if (flag == false)
                break;
        }
    }
};

int main()
{
    Restaurant restaurant;
    restaurant.run();

    return 0;
}
