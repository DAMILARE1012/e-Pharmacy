from .cart import Cart
from .stock import Stock
from .product import Product
from .prescription import Prescription
from datetime import datetime

import json

## would need to create a new object for each new order
class Wrapper:
    """
    Main class used to manage orders and carts.

    Attributes:
        sales: A list of the sales done during the program's execution
        stock: The stock used in the execution
        agentID: the username of the pharmacist running the program
    """
    def __init__(self, stock: Stock, agentID: str) -> None:
        self.sales = []
        self.stock = stock
        self.agentID = agentID

    def checkout(self, cart: Cart, customerID: str, prescription: Prescription = None):
        """Handles the checkout procedure of the program.
        
        Args:
            cart: The cart to pay for
            prescription: the prescription that accompanies the order (default: None)
        """

        #TODO: First check that all the product that require a prescription have all the criteria met
        # (i.e., (1) there is a prescription that (2) matches the customer's ID, and (3) contains the medication
        # in the specified quantity).
        # Raise an exception if either of those conditions is unmet.
        for product in cart.products:
            for stockItem in self.stock:
                if product == stockItem['code']:
                    #checking if drugs that need a prescription have a valid prescription
                    if stockItem['requires_prescription'] == True and prescription == None:
                        print(product+ " requires prescription. Please upload a valid prescription")
                        return None
                    #checking if the stock is of suitable quantity
                    if stockItem['quantity'] < cart.products[product]:
                        print("Insufficient quantity in stock. Only " + str(stockItem['quantity'])+" available")
                        return None
                    
        if prescription['CustomerID'] != customerID:
            print("The prescription and customer do not match")
            return None

        #TODO: Get the current datetime and save a Sale information for each product sold with the following schema
        # {"name": "<name>", "quantity": <quantity>, "price": <unit price>, "purchase_price": <total price>, "timestamp": <timestamp>,
        # "customerID": <customer username>, "salesperson": <pharmacist username>}
        presentDate = datetime.now()
        timeOfSale = datetime.timestamp(presentDate)*1000
        newSale = {}
        for product in cart.products:
            for stockItem in self.stock:
                if product == stockItem['code']:
                    newSale["name"] = stockItem['name']
                    newSale["quantity"] = stockItem['quantity']
                    newSale['price'] = stockItem['price']
                    newSale['purchase_price'] = (stockItem['quantity'] * stockItem['price'])
                    newSale['timestamp'] = timeOfSale
                    newSale['customerID'] = customerID
                    newSale['salesperson'] = self.agentID


        #TODO: Append the list to the current sales
                    self.sales.append(newSale)
                    #self.dump("data/sales.json")
        #TODO: Make sure that the sold products are marked as complete in the prescriptions.
                    soldProduct = Product(stockItem['code'],stockItem['name'],stockItem['brand'],stockItem['description'],stockItem['quantity'],stockItem['price'],stockItem['dosage_instruction'],stockItem['requires_prescription'],stockItem['category'])
                    soldPrescription = Prescription(prescription['DoctorName'],prescription['PrescriptionID'],prescription['Medications'],prescription['CustomerID'],str(timeOfSale))
                    soldPrescription.markComplete(soldProduct)
        print("Successful checkout")

    def dump(self, outfile: str):
        """Dumps the current sales data to a file

        Args:
            outfile: the path to the output file
        """
        #TODO: Load the content, if any of the existing file
        try:
            with open(outfile, 'r+') as f:
                salesData = json.load(f)
        #TODO: Update the content by appending the new entries to it, and save to the file
                salesData.append(self.sales)
                json.dump(salesData,f)
        except FileNotFoundError:
            print("File: " + outfile + " not found")