#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Item {
    int ID;
    string Name;
    double Price = 0;
    public:
        Item(int id, string name, double price){
            ID = id;
            Name = name;
            Price = price; 
        }

        void setID(int id) { ID = id; }
        void setName(string name) { Name = name; }
        void setPrice(double price) { Price = price; }
        void putDiscount(double percent){
            if (Price)  
                Price -= Price*(percent/100.0);
            else    
                cout << "Please Define Price First !!!";
        }
        
        void Display(bool showID = false){
            cout << left;
            if (showID){
                cout << setw(10) << ("ID: " + to_string(ID))  
                     << "| ";
            }
            cout << setw(15) << ("Item: " + Name) 
                 << "| " 
                 << "Price: $" << Price << "\n";
        }
};

void separator(char symbol, int length){
  for (int i=0;i<length;i++) cout << symbol;
  cout << '\n';
}

int main(){
    vector<Item> ItemVec;
    bool running = true;
    while (running){
        cout << "----{ SMART INVENTORY SYSTEM }----\n";
        cout <<  "1) Add Item\n2) Display Inventory \n3) Apply Discount\n4) Exit\n";
        cout << "[ Enter choice (1,2,3,4) ]-> ";
        int choice;
        cin >> choice;
        cout << '\n';
        switch (choice){
            case 1:{
                bool AddMore=true;
                while(AddMore){
                    int ItemID;
                    string ItemName;
                    double ItemPrice;
                    cout << "Enter Item ID: ";
                    cin >> ItemID;
                    separator('-',30);
                    cout << "Enter Item Name: ";
                    cin >> ItemName;
                    separator('-',30);
                    cout << "Enter Item Price: ";
                    cin >> ItemPrice;
                    separator('-',30);
                    ItemVec.push_back({ItemID, ItemName, ItemPrice});
                    cout << "Add More?...[Yes(1) | No(0)]: ";
                    cin >> AddMore;
                    if (AddMore) separator('~',35);
                }
                break;
            }

            case 2:{
                if (ItemVec.empty()){
                    cout << "No Items in Inventory to Display !\n";
                    break;
                }
                bool showID;
                cout << "Show ID? [Yes(1) | No(0)]: ";
                cin >> showID;
                separator('~',35);
                cout << "----[ INVENTORY ITEMS ]----\n";   
                for(Item item: ItemVec){
                    if (showID)
                        item.Display(showID);
                    else
                        item.Display();
                    }
                break; 
            }

            case 3:{
                if (ItemVec.empty()){
                    cout << "No Items in Inventory to Apply Discount !\n";
                    break;
                }
                double discountPercent;
                cout << "Enter Discount Percent: ";
                cin >> discountPercent;
                for(Item &item: ItemVec)
                    item.putDiscount(discountPercent);
                cout << "Discount Applied Successfully !\n";
                break;
            }

            case 4:
                cout << "Exiting System...Goodbye!\n";
                running=false;
                break;
        }
        cout << '\n';
    }
}