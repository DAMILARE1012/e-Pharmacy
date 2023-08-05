#include <iostream>
#include <string.h>
#include <chrono>
#include <random>
#include "ProductStruct.h"


using namespace std;
using namespace std::chrono;




class ProductClass{

    public:
    Product product;

    string generateUniqueCode()
    {
        string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

        string uniqueCode = "";
        auto now = system_clock::now();
        auto millis = duration_cast<milliseconds>(now.time_since_epoch());
        mt19937 generator(millis.count());
        uniform_int_distribution<int> distribution(0, 100000);

        // generate 32 characters long unique string

        for (int i = 0; i <= 10; i++)
        {
            int random_index = distribution(generator) % characters.length();
            uniqueCode += characters[random_index];
        }

        return uniqueCode;
    };

    int promptQuantity()
    {
        int qty;
        cout << "Enter Quantity for the product" << endl;
        
        // Write code to prompt user to enter the quantity and update the qty
        cin>>qty;
        if(cin.fail()){
            cout<< "Failed to enter qty"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cout<<"product quantity = " << qty<<endl;
        return qty;
    };

    float promptPrice()
    {
        float price;
        cout << "Enter Price for the product" << endl;

       // Write code to prompt user to enter the price for the product and update the price
       cin >> price;
        if(cin.fail()){
            cout<< "Failed to enter price"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } 
        cout<<"product price = " << price<<endl;
        return price;
    };

    string promptName()
    {
        string name;
        cout << "Enter Name for the product" << endl;
        
        // Write code to prompt user to enter the product name. Remember product can be more than word. e.g ("Fentanyl Patch")
        getline(cin, name);
        if(cin.fail()){
            cout<< "Failed to enter name"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cout<<"product name = " << name<<endl;
        return name;
    };

    string promptCategory()
    {
        string categ;
        cout << "Enter Category for the product" << endl;

        // Write code to prompt user to enter the product Category. Category can be more than one word. e.g ("infectious diseases")
        
        getline(cin, categ);
        if(cin.fail()){
            cout<< "Failed to enter category"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cout<<"product category = " << categ<<endl;
        return categ;
    };

    string promptDescription()
    {
        string desc;
        cout << "Enter Description for the product" << endl;

        // Write code to prompt user to enter the product description. description can be more than one word. e.g ("Drug for infectious diseases")
        getline(cin, desc);
        if(cin.fail()){
            cout<< "Failed to enter description"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cout<<"product description = " << desc<<endl;
        return desc;
    };

    string promptBrand()
    {
        string brand;
        cout << "Enter Brand for the product" << endl;

        // Write code to prompt user to enter the product brand. Brand can be more than one word. e.g ("Johnson & Johnson")
        getline(cin, brand);
        if(cin.fail()){
            cout<< "Failed to enter brand"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cout<<"product brand = " << brand <<endl;
        return brand;
    };

    string promptDosageInstruction()
    {
        string dsg_inst;
        cout << "Enter Dosage Instruction for the product" << endl;
        
        // Write code to prompt user to enter the product dosage instruction. Dosage instruction can be more than one word. e.g ("One tablet three times a day")
        getline(cin, dsg_inst);
        if(cin.fail()){
            cout<< "Failed to enter dosage instructions"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cout<<"product dosage instruction = " << dsg_inst <<endl;
        return dsg_inst;
    }

    bool promptRequirePrescription()
    {
        bool req_presc;
        cout << "Does This Product requires prescription? (1 for yes, 0 for no):" << endl;

        // Write code to prompt user to enter if the product requires prescription. Options is only 1 or 0
        cin >> req_presc;
        if(cin.fail()){
            cout<< req_presc <<" is not an appropriate choice"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> req_presc;
        }
        cout<<"requires prescription = " << req_presc<<endl;

        return req_presc;
    }

    Product createProduct()
    {

        // Write code to get all fields necessary to create a product by prompting user based on above methods
        product.code = generateUniqueCode();
        product.name = promptName();
        product.brand = promptBrand();
        product.category = promptCategory();
        product.description = promptDescription();
        product.dosageInstruction = promptDosageInstruction();
        product.requires_prescription = promptRequirePrescription();
        product.price = promptPrice();
        product.quantity = promptQuantity();   
        

        return product;
    };

    string toJson(Product prod)
    {

        string productInJson;

        // Write code to product into a json like format. Refer to product.json file for how product needs to formated.
        productInJson = "{\"code\":\"";
        productInJson.append(prod.code);

        productInJson.append("\",\"name\":\"");
        productInJson.append(prod.name);

        productInJson.append("\",\"brand\":\"");
        productInJson.append(prod.brand);

        productInJson.append("\",\"description\":\"");
        productInJson.append(prod.description);

        productInJson.append("\",\"dosage_instruction\":\"");
        productInJson.append(prod.dosageInstruction);

        productInJson.append("\",\"price\":\"");
        productInJson.append(to_string(prod.price));

        productInJson.append("\",\"quantity\":\"");
        productInJson.append(to_string( prod.quantity));

        productInJson.append("\",\"category\":\"");
        productInJson.append(prod.category);

        productInJson.append("\",\"requires_prescription\":\"");
        productInJson.append(to_string( prod.requires_prescription));

        productInJson.append("\"}")  ;     


        return productInJson;
    };


    Product fromJson(string txt)
    {

        Product prod;

        // Write convert a string of json like format to a product.


        return prod;
    };
};
