#include "SearchProduct.cpp"

class ProductManager
{
private:
    ProductClass pClass;
public:
    int getMenu(){

        bool isChoiceOk=false;
        int selectedChoice = -1;
        
        // Write code to show user the selection Menu as per shared sample output
        while (!isChoiceOk)
        {
            cout<<"Menu:"<<endl;
            cout<<"1. Add product"<<endl;
            cout<<"2. Search products by name"<<endl;
            cout<<"3. Search products by brand"<<endl;
            cout<<"4. Search products by category"<<endl;
            cout<<"5. Exit"<<endl;

            // User to enter a value between 1 and 5
            cout<<"Enter your choice: ";

            // Add here, code for reading user input and update user choice
            string selectedChoiceStr;
            getline(cin,selectedChoiceStr);
            stringstream(selectedChoiceStr) >> selectedChoice;
         
            if(cin.fail() || selectedChoice < 1 || selectedChoice > 5 ){

                cout<< selectedChoice << " is not a valid choice! "<<endl;
                cout<< "Enter a valid choice"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            else{
                isChoiceOk=true;
            }
        }
        
        
        return selectedChoice;
    }

    void addProduct(){
        Product p = pClass.createProduct();
        FileHandler fHandler;
        fHandler.saveToJsonFile(p);
    }
    
};

int main()
{

    Product prod;
    ProductManager prodManager;

    SearchProduct sProd;

    int choice = -1;

    // Write code handle selected choice.

    //display menu and get user input
    choice = prodManager.getMenu();

    while (choice != 5)
    {

        //Handling the Add product choice
        if(choice == 1){
            cout<<"Add a product: "<<endl;
            //call fn to add product
            prodManager.addProduct();
        }

        // Handling the ''search products by name' choice
        else if(choice == 2){
            string searchName;            
            getline(cin, searchName);
            if(cin.fail()){
            cout<< "Failed to enter search name"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sProd.searchByName(searchName); 
            }
        }

        // Handling the 'search products by brand' choice
        else if(choice == 3){
            string searchBrand;            
            getline(cin, searchBrand);
            if(cin.fail()){
            cout<< "Failed to enter search brand"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            sProd.searchByBrand(searchBrand);
            }
        }

        // Handling the 'search products by category' choice
        else if(choice == 4){
            string searchCategory;            
            getline(cin, searchCategory);
            if(cin.fail()){
                cout<< "Failed to enter search brand"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sProd.searchByCategory(searchCategory);
            }
        }
        return 0;
    }   
    cout<<"Exiting the Application...";

    return 0;
    
}


