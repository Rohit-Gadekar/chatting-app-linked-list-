#include <bits/stdc++.h>
using namespace std;

// Structure for a single message
struct MessageNode
{
    string text;
    string sender;
    time_t timestamp;
    MessageNode *next;

    MessageNode(string t, string s, time_t ts)
    {
        text = t;
        sender = s;
        timestamp = ts;
        next = NULL;
    }
};

// Adds a new message to the end of the linked list
void addMessage(string text, string sender, time_t timestamp, MessageNode *&head, MessageNode *&tail)
{
    MessageNode *newMessage = new MessageNode(text, sender, timestamp);

    // if the linked list is empty
    if (tail == nullptr)
    {
        head = newMessage;
        tail = newMessage;
    }
    else
    {
        tail->next = newMessage;
        tail = newMessage;
    }
}

// Displays all of the messages in the linked list
void displayMessages(MessageNode *head)
{
    for (MessageNode *current = head; current != nullptr; current = current->next)
    {
        cout << current->sender << " sent message at: " << ctime(&current->timestamp) << "mesage was: " << current->text << endl;
    }
}

// structure for user accounts
struct User
{
    string username;
    string password;
};

// Hash table for storing user accounts
unordered_map<string, User> users;

int main()
{
    // Initialize the head and tail pointers for the linked list of messages
    MessageNode *head = nullptr;
    MessageNode *tail = nullptr;

    // Initialize the user accounts
    users["rohit"] = {"rohit", "password123"};
    users["bob"] = {"bob", "qwerty"};
    users["charlie"] = {"charlie", "abc123"};

    string input;
    while (true)
    {
        cout << "Enter a command (login, exit): ";
        getline(cin, input);
        if (input == "exit")
        {
            break;
        }
        else if (input == "login")
        {
            string username;
            string password;
            int flag = 0;
            while (flag != 1)
            {
                cout << "\nEnter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (users.count(username) == 0 || users[username].password != password)
                {
                    flag = 0;
                    cout << "\nInvalid username or password." << endl;
                }
                else
                {
                    flag = 1;
                    cout << "\nSuccessfully logged in as " << username << "." << endl;
                }
            }

            int flag2 = 0;
            while (flag2 != 1)
            {
                string message;
                cout << "\nEnter a message (write 'exit' to end the conversation ): ";
                getline(cin, input);

                if (input == "exit")
                {
                    flag2 = 1;
                }
                
                else
                {
                    // Add the new message to the end of the linked list
                    time_t timestamp = time(nullptr);
                    addMessage(input, username, timestamp, head, tail);

                    // Send the message to the other user
                    cout << "Sending message to other user..." << endl;
                    // (Note: In a real-world chat application, you would need to use some kind of communication channel, such as a socket or HTTP request, to actually send the message to the other user)

                    // Wait for a response from the other user
                    string response;
                    cout << "Enter response from other user: ";
                    getline(cin, response);

                    // Add the response to the end of the linked list
                    time_t responseTimestamp = time(nullptr);
                    addMessage(response, "Other user", responseTimestamp, head, tail);
                }
            }

            // Display all of the messages in the linked list
            cout << "\n\nMessages:" << endl;
            displayMessages(head);
        }

        return 0;
    }
}
