#!/usr/bin/python3

from order_management import (
    UserManagement,
    Stock,
    Cart,
    Wrapper,
    Menu,
    BookRecords
)

if __name__ == '__main__':
    # files path declaration
    credentials_file = 'data/credentials.txt'
    stock_file = 'data/products.json'
    sales_file = 'data/sales.json'
    prescription_file = 'data/prescriptions.json'

    # load the user management file
    profiles = UserManagement.load(credentials_file)

    # get the logged in user
    pharmacist = profiles.get_logged_in_user()
    # make sure the logged in user is a pharmacist/salesperson
    assert pharmacist.role == 'salesperson', 'You are not allowed to access this feature.'

    # load the resources that we need
    stock = Stock.load(stock_file)
    cart = Cart(stock=stock)

    wrap = Wrapper(stock, pharmacist.username)
    books = BookRecords.load(sales_file)

    # create an instance of the menu
    menu = Menu(stock, profiles, pharmacist, sales_file, prescription_file, stock_file)

    # TODO: Using a while loop, show the menu to the user and guide them through the app
    #confirmExit is a variable used to exit from the infinite loop
    confirmExit = 0
    while confirmExit == 0 :
        #display the main menu
        mainMenuChoice = menu.get_main_menu()
        if(mainMenuChoice == '1' ):
            #go to the order sub menu
            orderMenuChoice = menu.get_order_menu()
            if(orderMenuChoice == '0'):
                continue
            elif(orderMenuChoice == '1'):
                addProdCode = input("Enter the product code: ")
                addQty = input("Enter the product quantity: ")
                try: 
                    addQty = int(addQty)
                    cart.add(addProdCode, addQty)
                except ValueError:
                    print("Invalid entry")
            elif(orderMenuChoice == '2'):
                rmProdCode = input("Enter the product code: ")
                cart.remove(rmProdCode)
            elif(orderMenuChoice == '3'):
                cart.clear()
            elif(orderMenuChoice == '4'):
                wrap.checkout(cart,)
            else:
                print("Invalid entry")

        elif(mainMenuChoice == '2'):
            #go to the analytics sub menu
            analyticsMenuChoice = menu.get_analytics_menu()
            if(analyticsMenuChoice == '0'):
                continue

        elif(mainMenuChoice == '0'):
            #Exit the app
            confirmExit = 1
            print("Exiting application...")

        else:
            print("Incorrect entry, try again")