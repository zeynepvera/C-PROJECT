

#ifndef NETWORK_H 
#define NETWORK_H


enum Skill
{

    JAVA,
    LINUX,
    PYTHON,
    MYSQL

};

 struct UserProfile
{

    int userID;
    char username[50];
    char fullName[100];

    enum Skill skills[4];

    void(*updateUser)(int,const char*, const char*); 


};

typedef struct Connection
{


    int connectionID;
    int user1ID;
    int user2ID;
}Connection;


void initialize();
void registerUser();
void updateUser(int userID, const char *newUsername, const char *newFullName);
void updateUserWrapper(int userID, const char *newUsername, const char *newFullName);
void deleteUser(int userID);
void connectUsers();
void endorseSkills();
void displayUsers(); 
void displayConnections(int userID);
void saveUsersToFile();
void loadUsersFromFile();
void saveConnectionsToFile();
void loadConnectionsFromFile();
int  areUsersConnected(int user1ID, int user2ID);
void cleanup();

#endif
