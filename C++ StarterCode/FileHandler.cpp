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

        // Add code here
        vector<Product> prodList;
        vector<string> prodLines;
        string prodLine;
        Product manProd;
        

        if (filename.empty()){
            filename = "data/products.json";
        }

        ifstream prodsFile(filename);

        while (getline(prodsFile, prodLine)){
             
                prodLines.push_back(prodLine);

                if(prodLine.substr(0,1) == "{"){

                    manProd.productFromJson(prodLine);
                    prodList.push_back(manProd);

                }
        }          
        prodsFile.close();
        return prodList;
    };

    void saveToJsonFile(Product p){

        vector<Product> pList;
        
        pList = readJsonFile();

        pList.push_back(p);

         // Check if the file exists.
        ifstream input_file(filename);

        if (!input_file.good()) {
            // The file does not exist.
            cout << "First Record ........." << endl;

            ofstream jsonFile(filename);

            jsonFile<<"["<<endl;
            jsonFile<< p.toJson()<<endl;
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
            jsonFile<< pList.at(i).toJson()<<","<<endl;
        }
        else{
            jsonFile<< pList.at(i).toJson()<<endl;
        }
    }
    jsonFile<<"]"<<endl;      

    jsonFile.close();
    }

    void saveToJsonFile(vector <Product> newProdList){
        vector<Product> pList;
        Product p;

        pList = readJsonFile();
        pList.clear();

        for(int i = 0; i < newProdList.size(); i++){
            p = newProdList.at(i);
            pList.push_back(p);
        }
        

        

         // Check if the file exists.
        ifstream input_file(filename);

        if (!input_file.good()) {
            // The file does not exist.
            cout << "First Record ........." << endl;

            ofstream jsonFile(filename);

            jsonFile<<"["<<endl;
            jsonFile<< p.toJson()<<endl;
            jsonFile<<"]"<<endl;

            return;
        jsonFile.close();
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
            jsonFile<< pList.at(i).toJson()<<","<<endl;
        }
        else{
            jsonFile<< pList.at(i).toJson()<<endl;
        }
    }
    jsonFile<<"]"<<endl;
    jsonFile.close();
    }
};