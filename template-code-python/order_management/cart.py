from .product import Product
from .stock import Stock

class Cart:
    """Represents a cart with a list of products and quantity

    Attributes:
        products: a dictionary with the key being the ID of the products, and the value being the quantity
        added
    """
    def __init__(self, stock: Stock) -> None:
        self.products = {}
        self.stock = stock

    def add(self, productCode: str, quantity: int):
        """Adds a product to the cart with the specified quantity
        
        Args:
            productCode: the identifier of the product
            quantity: quantity to add

        Returns: None
        """
        #TODO: Make sure the quantity is valid (> 0 and <= to the quantity in the stock)
        if(quantity <= 0):
            print("Enter a valid quantity")
            return None
        #find the product in stock that matches the code given
        stockItems = Stock(self.stock)
        prod = stockItems.getProductByID(productCode)
        if(prod == None):
            return None
        prodQty = int (prod['quantity'])
        if(quantity > prodQty):
            print("Sorry, the stock is not sufficient, only "+ str(prod['quantity'])	+" is available" )
            return None
        #TODO: If the product was already in the cart, increment the quantity
        if(prod['code'] in self.products):
            self.products[productCode] += quantity
            print("Added product to your cart successfully")
            print(self.products)
        #TODO: After the checks, add the product to the dictionary
        else:
            self.products[productCode] = quantity
            print("Added product to your cart successfully")
            print(self.products)
            

    def __str__(self) -> str:
        """String representation of the cart
        """
        #TODO: Return a string representation of a cart that shows the products, their quantity, unit price, total price. And also the total price of the cart
        # Feel free to format it the way you want to
        return NotImplemented

    def remove(self, code):
        """
        Removes a specific product from the cart """
        #TODO: Removes a product from the cart. safely fail if the product code is not found
        del self.products[code]
        print("New cart")
        print(self.products)


    def clear(self):
        """Clears up the cart.
        """
        self.products.clear()
        print("Cart cleared")


    @property
    def cost(self):
        """Returns the total cost of the cart"""
        #TODO: implement the function
        

    