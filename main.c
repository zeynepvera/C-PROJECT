#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "network.c"

int main()
{

    initialize();

    int choice;
    do
    {

        printf("\n === PROFESSIONAL SKILL NETWORK ===\n");
        printf("\n1.) Register\n");
        printf("2.) Update User\n");
        printf("3.) Delete User\n");
        printf("4.) Connect User\n");
        printf("5.) Are Users Connected?\n");
        printf("6.) Endorse Skills\n");
        printf("7.) Display Users\n");
        printf("8.) Display Connections\n");
        printf("0.) Exit\n");
        printf("\nEnter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            registerUser();
            break;

        case 2:
            updateUserWrapper(1, "newUsername", "newFullName");
            break;

        case 3:
            deleteUser(1);
            break;

        case 4:
            connectUsers();
            break;

        case 5:
            areUsersConnected(1, 2); 
            break;

        case 6:
            endorseSkills();
            break;

        case 7:
            displayUsers();
            break;

        case 8:
            displayConnections(1);
            break;

        case 0:
            printf(" Existing the Proffesional Skill Network. Bye!!\n");
            break;

        default:
            printf("Invalid choice. Please try again..\n");
            break;
        }

    } while (choice != 0);

    cleanup();

    return 0;
}