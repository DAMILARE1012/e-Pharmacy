#!/bin/bash

credentials_file="data/credentials.txt"

# Function to prompt for credentials
get_credentials() {
    # Write code read the user username and password 
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
    # Write your code here
    echo -e "Registration successful. You can now log in.\n"
}

# Function to verify credentials and privileges
verify_credentials() {
    local stored_cred=$(grep "^$user:" "$credentials_file" | cut -d ':' -f 2-)
    if [[ -n "$stored_cred" ]]; then
        local stored_pass=$(echo "$stored_cred" | cut -d ':' -f 1)
        local salt=$(echo "$stored_cred" | cut -d ':' -f 2)
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
    return 0  
}

# Function for the user menu
user_menu() {
    echo "This is a normal user menu..."
    exit 0
}

# Main script execution starts here
echo "Welcome to the authentication system."
# write a script that allows a system user to login, register, logout and exit from the system

