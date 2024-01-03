

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#define PRINT_ERROR(msg) printf("Error: %s\n", msg)

struct UserProfile *users = NULL;
 Connection *connections = NULL;
int userCount = 0;
int connectionCount = 0;
int userCapacity = 9;
int connectionCapacity = 9; 

void initialize()
{

    users = (struct UserProfile *)malloc(userCapacity * sizeof(struct UserProfile));
    connections = ( Connection *)malloc(connectionCapacity * sizeof( Connection));

    if (users == NULL || connections == NULL)
    {

        printf(" Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < userCapacity; i++)
    {
        users[i].updateUser = updateUserWrapper;
    }
    loadConnectionsFromFile();
    loadUsersFromFile();
}

void registerUser()
{


    printf("Enter username: ");
    scanf("%s", users[userCount].username);

    printf("Enter fullName: ");
    scanf("%s", users[userCount].fullName);


    users[userCount].userID = userCount + 1;

    printf("user %s registered with ID %d\n", users[userCount].username, users[userCount].userID);

    userCount++;
}

void updateUser(int userID, const char *newUsername, const char *newFullName)
{
    int targetUserID;
    if (userID == 1)
    {
        printf("Enter the user ID to update: ");
        scanf("%d", &targetUserID);
    }
    else
    {

        targetUserID = userID;
    }

    for (int i = 0; i < userCount; i++)
    {

        if (users[i].userID == targetUserID)
        {
            strcpy(users[i].username, newUsername);
            strcpy(users[i].fullName, newFullName);
            printf("User %d updated successfully.\n", targetUserID);

            return;
        }
    }
    printf("User with ID %d not found.\n", targetUserID);
}

void updateUserWrapper(int userID,const char*newUsername,const char *newFullName){

    updateUser(userID,newUsername,newFullName);
}
void deleteUser(int userID)
{
    int targetUserID;

    if (userID == 1)
    {
        printf("Enter the user ID to delete: ");
        scanf("%d", &targetUserID);
    }
    else
    {
        targetUserID = userID;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (users[i].userID == targetUserID)
        {
            for (int j = i; j < userCount - 1; j++)
            {
                users[j] = users[j + 1];
            }

            userCount--;
            printf("User %d deleted successfully.\n", targetUserID);
            return;
        }
    }

    printf("User with ID %d not found.\n", targetUserID);
}

int areUsersConnected(int user1ID, int user2ID)

{

    for (int i = 0; i < connectionCount; i++)
    {
        printf("Enter the first user's ID: \n");
        scanf("%d", &user1ID);
        printf("Enter the second user's ID: \n");
        scanf("%d", &user2ID);
        printf("Checking connection  %d - %d\n", connections[i].user1ID, connections[i].user2ID);

        if ((connections[i].user1ID == user1ID && connections[i].user2ID == user2ID) ||
            (connections[i].user1ID == user2ID && connections[i].user2ID == user1ID))
        {
            printf("Users are connected!");

            return 1; 
        }
    }

    printf("Users are not connected or the user(s) do not exist.\n");
    return 0; 
}

void connectUsers()
{

    int userID1, userID2;

    printf("Enter user 1' ID: ");
    scanf("%d", &userID1);

    printf("Enter user 2' ID: ");
    scanf("%d", &userID2);

    int isValidUser1 = 0, isValidUser2 = 0;

    for (int i = 0; i < userCount; i++)
    {
        if (users[i].userID == userID1)
        {
            isValidUser1 = 1;
            break;
        }
    }
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].userID == userID2)
        {
            isValidUser2 = 1;
            break;
        }
    }

    if (!isValidUser1 || !isValidUser2)
    {
        printf("Invalid user ID. Please enter valid user ID.\n");
        return;
    }

    if (userID1 == userID2)
    {
        printf("Cannot connects a user to itself.\n");
        return;
    }

    if (connectionCount == connectionCapacity)
    {

        // Resize the connections array if needed
        connectionCapacity *= 2;
        connections = realloc(connections, connectionCapacity * sizeof( Connection));

        if (connections == NULL)
        {
            printf("memory reallocation error.\n ");
            exit(EXIT_FAILURE);
        }
    }

    connections[connectionCount].connectionID = connectionCount + 1;
    connections[connectionCount].user1ID = userID1;
    connections[connectionCount].user2ID = userID2;
    printf("user %d and %d connected successfully!\n", userID1, userID2);

    connectionCount++;
}

void endorseSkills()
{

    int endorserID, endorsedID;

    enum Skill skill;

    printf("Enter endorser user ID: ");
    scanf("%d", &endorserID);

    printf("Enter endorsed user ID: ");
    scanf("%d", &endorsedID);

    printf("Choose skill to endorse ( 0-JAVA, 1-LINUX, 2-PYTHON, 3-MYSQL): ");
    scanf("%d", &skill);


    printf("User %d endorsed user %d for skill %d\n", endorserID, endorsedID, skill);
}
void displayUsers()
{


    printf("\n<<< User Profile >>>\n");

    if (userCount == 0)
    {

        printf("There is no user(s) to display!!!\n");
    }
    else
    {

        for (int i = 0; i < userCount; i++)
        {
            printf("\nFull Name: %s, User ID:%d, Username: %s\n", users[i].fullName, users[i].userID, users[i].username);
        }
    }
}
void displayConnections(int userID)
{

    printf("\n === Connections for User %d ===\n", userID);

    for (int i = 0; i < connectionCount; i++)
    {
        if (connections[i].user1ID == userID || connections[i].user2ID == userID)
        {
            int connectedUserID = (connections[i].user1ID == userID) ? connections[i].user2ID : connections[i].user1ID;
            printf("Connected User ID:%d\n", connectedUserID);
        }
    }
}

void saveUsersToFile()
{

    FILE *file = fopen("users.txt", "w");

    if (file == NULL)
    {

        printf(" Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%d %s %s\n", users[i].userID, users[i].username, users[i].fullName);
    }

    fclose(file);
}
void loadUsersFromFile()
{

    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {

        PRINT_ERROR("Error opening file for reading.\n");
        return;
       
    }
     while (fscanf(file, "%d %s %s", &users[userCount].userID, users[userCount].username, users[userCount].fullName) != EOF){

            userCount++;}
            
    fclose(file);
}

void saveConnectionsToFile()
{

    FILE *file = fopen("connections.txt", "w");
    if (file == NULL)
    {

        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < connectionCount; i++)
    {
        fprintf(file, "%d %d %d \n", connections[i].connectionID, connections[i].user1ID, connections[i].user2ID);
    }

    fclose(file);
}

void loadConnectionsFromFile()
{

    FILE *file = fopen("connections.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file for reading. \n");
        return;
    }

    while (fscanf(file, "%d %d %d", &connections[connectionCount].connectionID, &connections[connectionCount].user1ID, &connections[connectionCount].user2ID) != EOF)
    {
        connectionCount++;
    }
    fclose(file);
}

void cleanup()
{


    saveUsersToFile();
    saveConnectionsToFile();

    free(users);
    free(connections);
}
