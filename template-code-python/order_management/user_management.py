from __future__ import annotations

from .user import User
from typing import List

class UserManagement:
    """Main class to manage the user accounts

    Attributes:
        users: A list of users
        status_file: file where log ins are recorded
    """
    def __init__(self, status_file: str = 'data/.logged_in', users: List[User] = []) -> None:
        self.users = users
        self.status_file = status_file

    def get_logged_in_user(self) -> User:
        """Returns the logged in user
        """

        #TODO: Read the file, and return the object corresponding to the user in the file
        try:
            with open(self.status_file) as f:
                username = f.read().strip()
            user = self.get_user_details(username)  
            if user:
                print("You're welcome") # Print to test role attribute
                return user
        
        #TODO: If the account is not logged in (from the credentials file), raise an exception
            else:
                raise Exception("Logged in user not found")
        #TODO: Deal with the case where the file does not exist
        except FileNotFoundError:
            raise Exception("Status file not found") 

    def get_user_details(self, username: str) -> User:
        """Returns the account of a user
        
        Args:
            username: the target username
        """
        #TODO: Loop through the loaded accounts and return the one with the right username
        for user in self.users:
            if user.username == username:
                return user

        return None

    @staticmethod
    def load(infile: str = 'data/credentials.txt') -> UserManagement:
        """Loads the accounts from a file"""
        # open the file and retrieve the relevant fields to create the objects.
        #TODO: Nothing
        with open(infile, 'r') as f:
            users = [User(elements[0], elements[3], elements[4], bool(elements[5])) for line in f.readlines() if (elements := line.strip().split(':'))]
            return UserManagement(users=users)