#!/bin/bash

# Variables Definition
credentials_file="data/credentials.txt"
login_status=0

# Function to prompt for credentials
get_credentials() {
    # Write code read the user username and password 
    read -p "Username: " username
    read -s -p "Password: " password
    echo
    # The password must be invisible while typing to ensure that no one can read it while inserting it 
    return 0
}

# Function to generate a salted hash of the password
hash_password() {
    local salt=$(openssl rand -hex 8)
    local hashed_pass=$(echo -n "$1$salt" | sha256sum | awk '{print $1}')
    echo "$hashed_pass:$salt"
}

# Function to register new credentials
register_credentials() {
    # Insert code to register add the created user to a file called credentials.txt
    echo "----Registration----"
    read -p "Enter Username: " username_reg
    # Read password and ensure it's not empty
    while true; do
        read -s -p "Enter Password: " password_reg
        echo ""  # Add a newline after reading the password
        read -s -p "Confirm Password " password_reg2
        echo "" # Add a new line after reading the password

        if [ -z "$password_reg" ]; then
            echo "Password cannot be empty. Please try again."
        elif [ "$password_reg" != "$password_reg2" ]; then
            echo "Password not matching, please try again..."
            read -s -p "Enter Password Again: " password_reg
            echo ""  # Add a newline after reading the password
            read -s -p "Confirm Password Again: " password_reg2
            echo "" # Add a new line after reading the password
        else
            break
        fi
    done
    echo -n "Enter Full Name: "
    read full_name
    role=normal
        
    # Check if the user already exists
    if grep -q "^$username_reg:" "$credentials_file"; then
        echo "Error: User '$username_reg' already exists."
    else
    # Hash the input password
    local refined_password=$(hash_password "$password")
    # Append the collected records into the credential file.
        echo "$username_reg:$refined_password:$full_name:$role:$login_status" >> "$credentials_file"
        echo ""
        echo -e "User '$username_reg' Registration successful. You can now log in.\n"
    fi
}

# Login Function
login_user() {
echo "Welcome to the login page. Please enter your username and password."
    get_credentials
   
    # Check if the user exists...
    local user_info=$(grep "^$username:" "$credentials_file" | cut -d ':' -f 2-)
    if [[ -n "$user_info" ]]; then
        local stored_pass=$(echo "$user_info" | cut -d ':' -f 1)
        local salt=$(echo "$user_info" | cut -d ':' -f 2)
        local hashed_pass=$(echo -n "$pass$salt" | sha256sum | awk '{print $1}')
        local login_status=$(echo "$user_info" | cut -d ':' -f 5)
        local status=$(grep "^$username:" "$credentials_file")

        # Change the news state to 1
        if [[ "$login_status"=="0" ]]; then
            echo "You're welcome $username... You're the only active user for now..."
            new_status=$(echo "$status" | awk 'BEGIN{FS=OFS=":"} {$6="1"; print}')
            sed -i "s~$status~$new_status~" "$credentials_file"
        fi

        # Extract the value of the 'role' variable
        local user_role=$(echo "$user_info" | cut -d ':' -f 4)

        # Normal User - Display Dashboard
        if [ "$user_role" == "normal" ]; then
            user_menu
        # Admin User - Display Dashboard
        elif [ "$user_role" == "admin" ]; then
            admin_menu
        else
            salesperson_menu
        fi

    else
        echo -e "Unsuccessful login. Incorrect username or password. Please try again.\n" 
    fi
}

# Logout Function
logout_user() {
    local status=$(grep "^$username:" "$credentials_file")
    local login_status=$(echo "$status" | awk -F':' '{print $6}')

    if [[ "$login_status" == "1" ]]; then
        new_status=$(echo "$status" | awk 'BEGIN{FS=OFS=":"} {$6="0"; print}')
        sed -i "s~$status~$new_status~" "$credentials_file"
        echo -e "\nLogout successful..." 
        exit 0  
    fi
}

# Exit Function
exit_user(){
    echo "Exiting User System. Goodbye!"
    exit 0             
}


# Delete Function
delete_user(){
        echo -n "Enter the username to delete: "
        read del_username

        # Check if the username exists in the file
        if grep -q "^$del_username:" "$credentials_file"; then

            # Delete the line containing the username from the file
            sed -i "/^$del_username:/d" "$credentials_file"

            echo "User $del_username deleted from $credentials_file"
            admin_menu
            
        else
            echo "User $del_username not found in $credentials_file"
        fi
}

# ------------- Different Users Categories and Privileges -------------
# Admin Menu Function
admin_menu() {

        # Function to register new credentials
        adminReg_cred() {
        # Insert code to register add the created user to a file called credentials.txt
        echo "----Registration----"
        read -p "Enter Username: " username_reg_2
        read -s -p "Enter Password" password_reg_2
        echo "" # Add a newline after reading the password
        echo -n "Enter Full Name: "
        read full_name
        while true; do
        echo -n "Enter Role (admin/normal/salesperson): "
        read role

        case "$role" in
            admin|normal|salesperson)
                break  # Exit the loop when a valid role is entered
                ;;
            *)
                echo "Error: Invalid role. Please enter admin, normal, or salesperson."
                ;;
        esac
        done
        
        # Check if the user already exists
        if grep -q "^$username_reg_2:" "$credentials_file"; then
            echo "Error: User '$username_reg_2' already exists."
        else
        local refined_password=$(hash_password "$password")
            echo "$username_reg_2:$refined_password:$full_name:$role:0" >> "$credentials_file"
            echo ""
            echo -e "User '$username_reg_2' Registration successful. You can now log in.\n"
        fi

        
}
    # write a logic that allows a user logged in as admin to create an account. 
    # This function must allow the logged in user to create many users. 

            while true; do
                admin_display_menu
                read choice

                case "$choice" in
                    1)
                            adminReg_cred
                            ;;
                    2)      
                            delete_user
                            ;;
                    3)      
                            logout_user
                            ;;
                    *)
                        echo "Invalid choice. Please try again."
                        ;;
                esac

                echo ""
            done 
}

# Admin Display Menu  
admin_display_menu() {
    echo "Welcome to the admin dashboard."
    echo "1. Create an Account"
    echo "2. Delete an Account"
    echo "3. Logout"
    echo -n "Enter your choice: " 
}

# Function for the user menu
user_menu() {
    echo "This is the normal user menu..."
    echo "Options: "
    echo "1. Logout"
    echo "2. Exit"
    echo -n "Enter your choice: "
    read choice

    case "$choice" in
        1)
            logout_user
            ;;
        2)
            exit_user
            ;;
        *)
            echo "Invalid choice. Please try again."
            user_menu
            ;;
    esac
}

# Function for the Salesperson menu
salesperson_menu() {
    echo "This is the salesperson user menu..."
    echo "options: "
    echo "1. Logout"
    echo "2. Exit"
    echo -n "Enter your choice: "
    read choice

    case "$choice" in
        1)
                logout_user
                ;;
        2)
                exit_user
                ;;
        *)
            echo "Invalid choice. Please try again."
            salesperson_menu
            ;;
    esac
}


# The general display menu 
display_menu() {
    echo "Welcome to the authentication system."
    echo "1. Login"
    echo "2. Register"
    echo "3. Exit"
    echo -n "Enter your choice: "
}

# write a script that allows a system user to login, register, logout and exit from the system
while true; do
    display_menu
    read choice

    case "$choice" in
        1)
                login_user
                ;;
        2)
                register_credentials
                ;;
        3)
            exit_user
            break
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac

    echo ""
done