#include "FileHandler.cpp"

class SearchProduct
{
private:
    string filename;

public:
    string searchText;
    FileHandler fHandler;

    string to_lowercase(const string& text) {
        string lowercase_text;
        for (char c : text) {
            lowercase_text += tolower(c);
        }
        return lowercase_text;
    }

    vector<Product> searchByName(string name){

        // Add code Here
        vector<Product> prodList;
        vector<Product> foundProducts;
        Product product;
        prodList = fHandler.readJsonFile();

        for(int i=0; i< prodList.size(); i++){
            product = prodList.at(i);

            if( to_lowercase(product.name).find(to_lowercase(name)) != std::string::npos){
                foundProducts.push_back(product);
            }
        }
        return foundProducts;
    };

    vector<Product> searchByCategory(string categ){

        // Add code Here
        vector<Product> prodList;
        vector<Product> foundProducts;
        Product product;
        prodList = fHandler.readJsonFile();

        for(int i=0; i< prodList.size(); i++){
            product = prodList.at(i);

            if( to_lowercase(product.category).find(to_lowercase(categ)) != std::string::npos){
                foundProducts.push_back(product);
            }
        }
        return foundProducts;
    };

    vector<Product> searchByBrand(string brand){
        // Add code here
        vector<Product> prodList;
        vector<Product> foundProducts;
        Product product;
        prodList = fHandler.readJsonFile();

        for(int i=0; i< prodList.size(); i++){
            product = prodList.at(i);

            if( to_lowercase(product.brand).find(to_lowercase(brand)) != std::string::npos){
                foundProducts.push_back(product);
            }
        }
        return foundProducts;
    };

    void showSearchResult(vector<Product> plist, string sTxt)
    {
        // Add code Here
        ProductClass pClass;
        Product p;

        cout<<"Result for "<<sTxt<< " Products in Json Format:\n"<<endl;
        cout<<"..........................."<<endl;
        for(int i=0; i< plist.size();i++){
            p = plist.at(i);
            cout<< pClass.toJson(p)<<endl;
        }

        cout<<"..........................."<<endl;

    }
};