from . import Stock, Cart, User, UserManagement, BookRecords, Wrapper, Prescription

MSG_WRONG_INPUT = "Wrong input. Try again!"
class Menu:
    """Represents the menu class for the project

    Attributes: 
        stock: stock variable
        profiles: user management module
        pharmacist: account of the salesperson
        records_file: path to the file containing the sales
        prescriptions_file: path to the file containing the prescriptions.
        stock_file: path to the file containing the stock data
    """
    def __init__(self, stock: Stock, profiles: UserManagement, pharmacist: User, records_file: str, prescriptions_file: str, stock_file: str) -> None:
        self.stock = stock
        self.profiles = profiles
        self.pharmacist = pharmacist
        self.cart = Cart(stock = stock)
        # use the file instead of the object so that we can keep track
        self.records_file = records_file
        self.prescriptions_file = prescriptions_file
        self.stock_file = stock_file

    #TODO: Create all the necessary functions/method to create and manage the menu using the
    # available variables and all the attributes of the class
    def get_main_menu(self):
        print("*************************************")
        print("Order management and analytics menu")
        print("[loc: .]")
        print("*************************************\n")
        print("1. Order management")
        print("2. Get analytics")
        print("0. Exit application")
        choice = input("Your choice: ")
        return choice

    def get_order_menu(self):
        print("*************************************")
        print("Order management and analytics menu")
        print("[loc: .order.]")
        print("*************************************\n")
        print("1. Add to cart")
        print("2. Remove from cart")
        print("3. Clear cart")
        print("4. Checkout")
        print("0. Back")
        choice = input("Your choice: ")
        return choice

    def get_analytics_menu(self):
        print("*************************************")
        print("Order management and analytics menu")
        print("[loc: .analytics.]")
        print("*************************************\n")
        print("1. Total income from purchases")
        print("2. Prescription statistics")
        print("3. Purchases for a user")
        print("4. Sales by an agent")
        print("5. Top sales")
        print("0. Back")
        choice = input("Your choice: ")
        return choice

    # Make sure to dump the prescriptions, stock, and sale data after every sale.

    # Your menu should have two main options with suboptions. Such as
    """
    1. Order management
        1.1. Adding to a cart (you need to show the list of products and ask the user to select one with ID. Bonus: Can you display with numbers and ask user to choose a number instead?
                Also ask for quantity.)
        1.2. Remove from a cart (display the cart and ask the user to select the element to remove. Remove by ID or by index (bonus))
        1.3. Clear the cart (self explanatory)
        1.4. Checkout (displays the cart with the total and ask for a prescription element. Proceed to checkout and show a message is successful or not).
    2. Analytics
        2.1. Total income from purchases
        2.2. Prescription statistics
        2.3. Purchases for a user
        2.4. Sales by an agent
        2.5. Top sales

    * For each of the menu items, when necessary, display a success or error message to guide the user.
    """

    # **CHALLENGE** (BONUS): Can you implement the menu to work as a USSD application? Implement and show your design