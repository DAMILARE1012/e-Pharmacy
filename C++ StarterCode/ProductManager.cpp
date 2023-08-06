#include "SearchProduct.cpp"

class ProductManager
{
private:
    Product prod;
public:
    int getMenu(){

        // TODO Add code to display Menu
        // Menu should have 
        // Add Product
        //Search Product By Name
        //Search Product By Category
        //Search Product By Brand
        // Update Product
        // Delete Product
        bool isChoiceOk=false;
        int selectedChoice = -1;
        
        // Write code to show user the selection Menu as per shared sample output
        while (!isChoiceOk)
        {
            cout<<"Menu:"<<endl;
            cout<<"1. Add product"<<endl;
            cout<<"2. Search products by name"<<endl;
            cout<<"3. Search products by category"<<endl;
            cout<<"4. Search products by brand"<<endl;
            cout<<"5. Update product"<<endl;
            cout<<"6. Delete product"<<endl;
            cout<<"7. Exit"<<endl;

            // User to enter a value between 1 and 5
            cout<<"Enter your choice: ";

            // Add here, code for reading user input and update user choice
            string selectedChoiceStr;
            getline(cin,selectedChoiceStr);
            stringstream(selectedChoiceStr) >> selectedChoice;
         
            if(cin.fail() || selectedChoice < 1 || selectedChoice > 7 ){

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
        // TODO add code to add product and 
        // store the product to products.json file by using Product class and FileHandler class
        prod.createProduct();
        FileHandler fHandler;
        fHandler.saveToJsonFile(prod);
    }

    // TODO Add code for Updating a product
    void updateProduct(string productCode){
        
    }
    // TODO Add code for deleting a product
    void deleteProduct(string productCode){

    }
    
};

int main()
{

    // ADD Code for displaying a welcome Menu
    // and handle all required logic to add, search, update, and delete product
    Product prod;
    ProductManager prodManager;
    SearchProduct sProd;

    int choice = -1;
    choice = prodManager.getMenu();

    while (choice != 7)
    {

        //Handling the Add product choice
        if(choice == 1){
            cout<<"Add a product: "<<endl;
            //call fn to add product
            prodManager.addProduct();
        }

        // Handling the ''search products by name' choice
        else if(choice == 2){
            cout <<"Enter the product name: ";
            string searchName;            
            getline(cin, searchName);
            if(cin.fail()){
                cout<< "Failed to enter search name"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            vector<Product> foundProducts;
            foundProducts=sProd.searchByName(searchName);
            sProd.showSearchResult(foundProducts, searchName);
            
        }

        // Handling the 'search products by category' choice
        else if(choice == 3){
            cout <<"Enter the product category: ";
            string searchCategory;            
            getline(cin, searchCategory);
            if(cin.fail()){
                cout<< "Failed to enter search brand"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            vector<Product> foundProducts;
            foundProducts = sProd.searchByCategory(searchCategory);
            sProd.showSearchResult(foundProducts, searchCategory);
        }

        // Handling the 'search products by brand' choice
        else if(choice == 4){
            cout <<"Enter the product brand: ";
            string searchBrand;            
            getline(cin, searchBrand);
            if(cin.fail()){
                cout<< "Failed to enter search brand"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            vector<Product> foundProducts;
            foundProducts = sProd.searchByBrand(searchBrand);
            sProd.showSearchResult(foundProducts, searchBrand);
        }
        // Handling the 'update product' choice
        else if(choice == 5){
           string productCode;
           prodManager.updateProduct(productCode);             
        }
        // Handling the 'delete product' choice
        else if(choice == 6){
            string productCode;
            prodManager.deleteProduct(productCode);
        }

        cout<<"Exiting the Application..."<<endl;
        return 0;
    }   
    cout<<"Exiting the Application..."<<endl;


    return 0;
}


