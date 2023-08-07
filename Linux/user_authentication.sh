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
    read -s -p "Enter Password" password_reg
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
    if grep -q "^$username_reg:" "$credentials_file"; then
        echo "Error: User '$username_reg' already exists."
    else
    local refined_password=$(hash_password "$password")
        echo "$username_reg:$refined_password:$full_name:$role:$login_status" >> "$credentials_file"
        echo ""
        echo -e "User '$username_reg' Registration successful. You can now log in.\n"
    fi
}

# Function to verify credentials and privileges
verify_credentials() {
    
    local user_info=$(grep "^$user:" "$credentials_file" | cut -d ':' -f 2-)
    if [[ -n "$user_info" ]]; then
        local stored_pass=$(echo "$user_info" | cut -d ':' -f 1)
        local salt=$(echo "$user_info" | cut -d ':' -f 2)
        local hashed_pass=$(echo -n "$pass$salt" | sha256sum | awk '{print $1}')
        
        # check whether the credentials provided are accurate 
      -  	# Write here
            # On successful login remember to update the credentials.txt file for login status to 1
 	# if the credentials provided are correct, check the role. If the role is admin, call the admin menu
 		# write here
 	# Otherwise call user menu
 		# Write your code here
    fi
    echo -e "Unsuccessful login. Incorrect username or password. Please try again.\n"
    return 1
}

# Function for the admin menu
admin_menu() {

    # write a logic that allows a user logged in as admin to create an account. 
    # This function must allow the logged in user to create many users. 
    
    # Write your code here  
    admin_display_menu() {
                echo "Welcome to the admin dashboard."
                echo "1. Create an Account"
                echo "2. Logout"
                echo "3. Exit"
                echo -n "Enter your choice: "
            }

            while true; do
                admin_display_menu
                read choice

                case "$choice" in
                    1)
                            register_credentials
                            ;;
                    2)      
                            logout_user
                            return
                            ;;
                    3) 
                            exit_user
                            ;;
                    *)
                        echo "Invalid choice. Please try again."
                        ;;
                esac

                echo ""
            done 
}

# Function for the user menu
user_menu() {
    echo "This is a normal user menu..."
    exit 0
}

# Main script execution starts here
# Function to display the menu
display_menu() {
    echo "Welcome to the authentication system."
    echo "1. Login"
    echo "2. Register"
    echo "3. Logout"
    echo "4. Exit"
    echo -n "Enter your choice: "
}
# write a script that allows a system user to login, register, logout and exit from the system

# Function to handle user login
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
        
        # Change the news state to 1
        local status=$(grep "^$username:" "$credentials_file")
        if [[ "$login_status"=="0" ]]; then
            echo "You're welcome $username... You're the only active user for now..."
            new_status=$(echo "$status" | awk 'BEGIN{FS=OFS=":"} {$6="1"; print}')
            sed -i "s~$status~$new_status~" "$credentials_file"
        fi

        # Admin Privilege
        if [[ "$role"=="admin" ]]; then
            admin_menu
        fi

    else
        echo -e "Unsuccessful login. Incorrect username or password. Please try again.\n" 
    fi
        
}

# Function to handle user logout
logout_user() {
    # Change the news state to 0
        local status=$(grep "^$username:" "$credentials_file")
        if [[ "$login_status"=="1" ]]; then
            echo "Updating login status to 0"
            new_status=$(echo "$status" | awk 'BEGIN{FS=OFS=":"} {$6="0"; print}')
            sed -i "s~$status~$new_status~" "$credentials_file"
            echo "Logout successful..."
        fi
        return
}

exit_user(){
    # Change the news state to 0
        local status=$(grep "^$username:" "$credentials_file")
        if [[ "$login_status"=="1" ]]; then
            echo "Updating login status to 0"
            new_status=$(echo "$status" | awk 'BEGIN{FS=OFS=":"} {$6="0"; print}')
            sed -i "s~$status~$new_status~" "$credentials_file"
            echo "Exiting User System. Goodbye!"
            exit 0   
        fi
          
}

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
            if [ -n "$username" ]; then
                logout_user
                
            else
                echo "You are not logged in."
            fi
            ;;
        4)
            exit_user;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac

    echo ""
done