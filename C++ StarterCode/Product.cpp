#include <iostream>
#include <string.h>
#include <chrono>
#include <random>


using namespace std;
using namespace std::chrono;



class Product{

    private:
    int quantity;
    string name;
    string brand;
    string description;
    string code;
    float price;
    string dosageInstruction;
    string category;
    bool requires_prescription;

    public:

    string getName(){
        //TODO Add code that return the Product Name
        return name;
    }

    string getBrand(){
        //TODO Add code that return the Product Brand
        return brand;
    }

    string getDecrisption(){
        //TODO Add code that return the Product Description
        return description;
    }

    string getDosageInstraction(){
        //TODO Add code that return the Product Dosage Instruction
        return dosageInstruction;
    }

    string getCategory(){
        //TODO Add code that return the Product Category
        return category;
    }
    
    int getQuantity(){
        //TODO Add code that return the Product Quantity
        return quantity;
    }

    float getPrice(){
        //TODO Add code that return the Product Price
        return price;
    }

    bool getRequiresPrescription(){
        //TODO Add code that return Product Requires Prescription status
        return requires_prescription;
    }


    string generateUniqueCode()
    {
        string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

        string uniqueCode = "";
        auto now = system_clock::now();
        auto millis = duration_cast<milliseconds>(now.time_since_epoch());
        mt19937 generator(millis.count());
        uniform_int_distribution<int> distribution(0, 100000);

        // generate 10 characters long unique string

        for (int i = 0; i <= 10; i++)
        {
            int random_index = distribution(generator) % characters.length();
            uniqueCode += characters[random_index];
        }

        return uniqueCode;
    };

    string promptTextField(string promptText){

        // TODO Add code to prompt user for input for any Product string field
        // method takes text to display e.g: "Enter Product Name:"
        // it prompts a user and return user input in form of text. Text can be made by multiple words.
        string usrInput;
        cout << "Enter the "<<promptText<<" for the product: ";
        getline(cin, usrInput);
        return usrInput;
    }

    float promptNumberField(string promptText){
        // TODO Add code to prompt user for input for any Product Numeric field
        // method takes text to display e.g: "Enter Product Name:"
        // it prompts a user and return user input in form of text. Text can be made by multiple words.
        float usrInput;
        string usrInputStr;

        cout << "Enter the "<<promptText<<" for the product: ";
        getline(cin,usrInputStr);
        stringstream(usrInputStr) >> usrInput;

        return usrInput;
    }

    bool promptRequirePrescription()
    {
        // TODO Add code to prompt user for choosing if Product requires prescription.
        // User can type 1 or 0. 
        // it prompts a user and return user input in form of boolean.
        bool usrInput;
        string usrInputStr;
        cout << "Does This Product requires prescription? (1 for yes, 0 for no):";
        getline(cin,usrInputStr);
        stringstream(usrInputStr) >> usrInput;
        return usrInput;
    }

    void createProduct()
    {
        // TODO Add code that calls promptTextField() method and prompt user for entering product name and update the name field.
        name = promptTextField("name");
        // TODO Add code that calls promptTextField() method and prompt user for entering product brand and update the brand field.
        brand = promptTextField("brand");
        // TODO Add code that calls promptTextField() method and prompt user for entering product description and update the decription field.
        description = promptTextField("description");
        // TODO Add code that calls promptTextField() method and prompt user for entering product category and update the category field.
        category = promptTextField("category");
        // TODO Add code that calls promptTextField() method and prompt user for entering product dosageInstruction and update the dosage instruction field.
        dosageInstruction = promptTextField("dosage instruction");
        // TODO Add code that calls promptNumberField() method and prompt user for entering product quantity and update the quantity field.
        quantity = promptNumberField("quantity");
        // TODO Add code that calls promptNumberField() method and prompt user for entering product price and update the price field.
        price = promptNumberField("price");
        // TODO Add code that calls promptRequirePrescription() method and prompt user for entering product requires presc and update the requiresprescription field.
        requires_prescription = promptRequirePrescription();
        // Add code to generate Unique code for product using generateUniqueCode method
        code = generateUniqueCode();       
    };

    void updateProductField(int updateAttribute){
        switch (updateAttribute)
            {
            case 1:
                price = promptNumberField("price");
                break;
            case 2:
                quantity = promptNumberField("quantity");
                break;            
            default:
                cout<<"Incorrect entry!"<<endl;
                break;
            } 
    }

    string toJson()
    {

        string productInJson;

      // TODO Add code for converting a product to json form from the private declared attributes.
      // The Output should look like:
      //{"code":"tgtwdNbCnwx","name":"name 1","brand":"br 2","description":"df","dosage_instruction":"dfg","price":123.000000,"quantity":13,"category":"des","requires_prescription":1}
        productInJson = "{\"code\":\"";
        productInJson.append(code);

        productInJson.append("\",\"name\":\"");
        productInJson.append(name);

        productInJson.append("\",\"brand\":\"");
        productInJson.append(brand);

        productInJson.append("\",\"description\":\"");
        productInJson.append(description);

        productInJson.append("\",\"dosage_instruction\":\"");
        productInJson.append(dosageInstruction);

        productInJson.append("\",\"price\":");
        productInJson.append(to_string(price));

        productInJson.append(",\"quantity\":");
        productInJson.append(to_string( quantity));

        productInJson.append(",\"category\":\"");
        productInJson.append(category);

        productInJson.append("\",\"requires_prescription\":");
        productInJson.append(to_string( requires_prescription));

        productInJson.append("}") ;

        return productInJson;
    };


    
    void productFromJson(string txt)
    {
        //TODO Add code to convert a json string product to product object
        // string is in the form below
        //{"code":"tgtwdNbCnwx","name":"name 1","brand":"br 2","description":"df","dosage_instruction":"dfg","price":123.000000,"quantity":13,"category":"des","requires_prescription":1}
        // You need to extract value for each field and update private attributes declared above.
        string delimiterFinal =  "}";
        int delimFinal = txt.find(delimiterFinal);

        int delim1 = 0;
        int delim2 = 0;
        int count = 0;
        while(count < 10) {                
            string delimiterStart = ":";
            string delimiterEnd = ",";         

            int str_len = txt.size();
            //if empty
            if(str_len<1){
                break;
            }

            delim1 = txt.find(delimiterStart, delim1+1);
            delim2 = txt.find(delimiterEnd, delim2+1);
            

            string jsonSubstr = txt.substr((delim1+1) , (delim2 - delim1 - 1 ) );
            
            count ++;
            switch (count)
            {
            case 1:
                jsonSubstr = cleanString(jsonSubstr);
                code = jsonSubstr;
                break;
            case 2:
                jsonSubstr = cleanString(jsonSubstr);
                name = jsonSubstr;
                break;
            case 3:
                jsonSubstr = cleanString(jsonSubstr);
                brand = jsonSubstr;
                break;
            case 4:
                jsonSubstr = cleanString(jsonSubstr);
                description = jsonSubstr;
                break;
            case 5:
                jsonSubstr = cleanString(jsonSubstr);
                dosageInstruction = jsonSubstr;
                break;
            case 6:
                price = stof(jsonSubstr);
                break;
            case 7:
                quantity = stoi(jsonSubstr);
                break;
            case 8:
                jsonSubstr = cleanString(jsonSubstr);
                category = jsonSubstr;
                break;
            case 9:
                requires_prescription = stoi(jsonSubstr);
                break;

            default:
                break;
            }

            }
    };

    string cleanString(string txt)
    {
        char *s = (char *)calloc(txt.length() - 2, sizeof(char));
        int c = 0;
        for (int i = 1; i < txt.length() - 1; i++)
        {
            if (txt[i] == '"')
                break;
            s[c] = txt[i];
            c++;
        }
        return s;
    }

};
