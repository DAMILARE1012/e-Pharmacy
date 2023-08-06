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

        // TODO
        //Add code to search by name. Searching is not case sensitive it means 
        //for input like: "name" products with names like "Name 1", "Product name" needs to included in the found results.
        
        vector<Product> prodList;
        vector<Product> foundProducts;
        Product product;
        prodList = fHandler.readJsonFile();

        for(int i=0; i< prodList.size(); i++){
            product = prodList.at(i);

            if( to_lowercase(product.getName()).find(to_lowercase(name)) != std::string::npos){
                foundProducts.push_back(product);
            }
        }
        return foundProducts;
    
    };

    vector<Product> searchByCategory(string categ){

        // TODO
        //Add code to search by category. Searching is not case sensitive it means 
        //for input like: "categ" products with category like "category 1", "Product category" needs to included in the found results.
        vector<Product> prodList;
        vector<Product> foundProducts;
        Product product;
        prodList = fHandler.readJsonFile();

        for(int i=0; i< prodList.size(); i++){
            product = prodList.at(i);

            if( to_lowercase(product.getCategory()).find(to_lowercase(categ)) != std::string::npos){
                foundProducts.push_back(product);
            }
        }
        return foundProducts;
    };

    vector<Product> searchByBrand(string brand){
      // TODO
        //Add code to search by brand. Searching is not case sensitive it means 
        //for input like: "br" products with names like "Brand 1", "brand name" needs to included in the found results.
        vector<Product> prodList;
        vector<Product> foundProducts;
        Product product;
        prodList = fHandler.readJsonFile();

        for(int i=0; i< prodList.size(); i++){
            product = prodList.at(i);

            if( to_lowercase(product.getBrand()).find(to_lowercase(brand)) != std::string::npos){
                foundProducts.push_back(product);
            }
        }
        return foundProducts;
    };

    void showSearchResult(vector<Product> plist, string sTxt)
    {
        // TODO
        //Add code to display Search results

        Product p;

        cout<<"Result for "<<sTxt<< " Products in Json Format:\n"<<endl;
        cout<<"..........................."<<endl;
        for(int i=0; i< plist.size();i++){
            p = plist.at(i);
            cout<< p.toJson()<<endl;
        }

        cout<<"..........................."<<endl;
    }
};