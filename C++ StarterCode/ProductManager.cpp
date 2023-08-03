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

    return 0;
}


