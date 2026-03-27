#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

enum ItemCategory {ELECTRONICS, FOOD, CLOTHING};

struct Item {
    string name;
    double price;
    ItemCategory category;
};

void Display(Item *ptr){    
    cout << left;
    cout << setw(15) << ("Item: "+ptr->name) 
         << "| " 
         << "Price: $" << ptr->price << "\n";
}

void ApplyDiscount(double &price, double percent){
    price -= (price * (percent / 100));
}

void separator(char symbol, int length){
  for (int i=0;i<length;i++) cout << symbol;
  cout << '\n';
}

int main(){ 
    Item* ItemArr=nullptr;
    int CurrentSize=0;
    bool running=true;
    while (running){
        cout << "----{ INVENTORY SYSTEM }----\n";
        cout <<  "1) Add Item\n2) Display Inventory\n3) Apply Discount\n4) Exit\n";
        cout << "[ Enter choice (1,2,3,4) ]-> ";
        int choice;
        cin >> choice;
        separator('~',35);
        switch (choice){
            case 1:{
                bool AddMore=true;
                while(AddMore){
                    Item item;
                    int CategoryNum;
                    cout << "Enter Item Name: ";
                    cin >> item.name;
                    separator('-',30);
                    cout << "Enter Item Price: ";
                    cin >> item.price;
                    separator('-',30);
                    cout << "Select Item Category:-\n1. Electronics\n2. Food\n3. Clothing\n";
                    cout << "Choice...[1,2,3]: ";
                    cin >> CategoryNum;
                    item.category = (ItemCategory)(--CategoryNum);
                    separator('-',30);

                    //Create a new larger block of memory
                    Item* temp=new Item[CurrentSize+1];
                    //Copy data from old block to the new one
                    for (int i=0;i<CurrentSize;i++)
                        temp[i]=ItemArr[i];
                    //Add new data
                    temp[CurrentSize]=item;
                    //Increment CurrentSize
                    CurrentSize++;
                    //Release the old block
                    delete[] ItemArr;
                    //Re-assign to old block
                    ItemArr=temp;

                    cout << "Add More?...[Yes(1) | No(0)]: ";
                    cin >> AddMore;
                    if (AddMore) separator('~',35);
                }
                break;
            }

            case 2:{
                if (CurrentSize==0){
                    cout << "No Items in Inventory to Display!\n";
                    break;
                }
                cout << "----[ INVENTORY ITEMS ]----\n";   
                for(int i=0;i<CurrentSize;i++)
                Display(&ItemArr[i]);
                break; 
            }
            
            case 3:{
                if (CurrentSize==0){
                    cout << "No Items in Inventory to Apply Discount!\n";
                    break;
                }
                double discountPercent;
                cout << "Enter Discount Percent: ";
                cin >> discountPercent;
                for(int i=0;i<CurrentSize;i++)
                    ApplyDiscount(ItemArr[i].price, discountPercent);
                cout << "Discount Applied Successfully!\n";
                break;
            }

            case 4:
                cout << "Exiting System...Goodbye!\n";
                running=false;
                break;
        }
        separator('~',35);
    }
    //Release the ItemArr block
    delete[] ItemArr;
    return 0;
}