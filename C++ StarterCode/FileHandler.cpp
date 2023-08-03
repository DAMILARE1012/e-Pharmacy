#include <sstream>
#include <vector>
#include <string.h>
#include <fstream>
#include <stdio.h>

//Importing Product class
#include "Product.cpp"

using namespace std;

class FileHandler{
    public:
    string filename;

    vector<Product> readJsonFile(){

        vector<Product> prodList;
        vector<string> prodLines;
        string prodLine;
        ProductClass manProd;
        Product product;
        

        if (filename.empty()){
            filename = "data/products.json";
        }

       

        ifstream prodsFile(filename);

        while (getline(prodsFile, prodLine)){
             
                prodLines.push_back(prodLine);

                if(prodLine.substr(0,1) == "{"){

                    
                    product = manProd.fromJson(prodLine);
                    prodList.push_back(product);

                }
        }          
        
       

        return prodList;
    };

    void saveToJsonFile(Product p){

        vector<Product> pList;
        ProductClass pClass;


        pList = readJsonFile();

        pList.push_back(p);

         // Check if the file exists.
        ifstream input_file(filename);

        if (!input_file.good()) {
            // The file does not exist.
            cout << "First Record ........." << endl;

            ofstream jsonFile(filename);

            jsonFile<<"["<<endl;
            jsonFile<< pClass.toJson(p)<<endl;
            jsonFile<<"]"<<endl;

            return;

        }

        // Delete the file.
    int ret = remove(filename.c_str());
    if (ret != 0) {
        std::cout << "Error deleting file: " << strerror(errno) << "\n";
        return ;
    }

    ofstream jsonFile(filename);
    jsonFile<<"["<<endl;
    for(int i=0; i<pList.size(); i++){

        if(i< pList.size() -1){
            jsonFile<< pClass.toJson(pList.at(i))<<","<<endl;
        }
        else{
            jsonFile<< pClass.toJson(pList.at(i))<<endl;
        }
    }
    jsonFile<<"]"<<endl;      


    }
};