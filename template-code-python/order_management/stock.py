import json
from typing import List
from .product import Product

class Stock:
    """Represents the catalog of products
    
    Attributes:
        products: the list of products
    """
    def __init__(self, products: List[Product]) -> None:
        self.products = products

    def update(self, id: int, change: int):
        """Update the quantity of a product by adding or removing
        
        Args:
            id: identifier of the product
            change: the value by which the quantity should be update (+1 adds 1, -2 removes 2 for example)
        """
        #TODO: Make sure the product exists, and that by making the change, the value is still >= 0
        
        #TODO: Update the quantity

    def getProductByID(self, id: str) -> Product:
        """Gets a product by its ID

        Args:
            id: identifier of the product
        
        Returns: the product's object
        """
        #TODO: Implement the function
        count = 0
        for prod in self.products:
            if prod['code'] == id:
                count += 1
                return prod
        if count == 0:
            print(id + " not found")

    def dump(self, outfile: str):
        """Saves the stock to a JSON file"""
        #TODO: Implement the function
        try:
            with open(outfile, 'w') as f:
                json.dump(self.products, f)
        except FileNotFoundError:
            print("File: " + outfile + " not found")
        

    
    @staticmethod
    def load(infile: str):
        """Loads the stock from an existing file
        
        Args: 
            infile: input file to the function
        """
        #TODO: Implement the function
        try:
            with open(infile, 'r') as f:
                stockData = json.load(f)
                return stockData
        except FileNotFoundError:
            print("File: " + infile + " not found")

    
    def __str__(self) -> str:
        """Returns a string representation of the stock
        """
        #TODO: Return the description of the stock with a nice output showing the ID, Name, Brand, Description, Quantity, Price, and the requires_prescription field