#include <stdio.h>
#include <string.h>

struct Request
{
    char rid[10];
    char loc[100];
    int people;
    char emer[20];
    char res[100];
    char team[50];
    char status[20];
    int priority;
};

int getPriority(char emer[])
{
    if (strcmp(emer, "Critical") == 0)
        return 1;
    else if (strcmp(emer, "High") == 0)
        return 2;
    else if (strcmp(emer, "Medium") == 0)
        return 3;
    else
        return 4;
}

void display(struct Request r)
{
    printf("\nRequest ID : %s", r.rid);
    printf("\nLocation   : %s", r.loc);
    printf("\nPeople     : %d", r.people);
    printf("\nEmergency  : %s", r.emer);
    printf("\nResources  : %s", r.res);
    printf("\nTeam       : %s", r.team);
    printf("\nStatus     : %s", r.status);
    printf("\nPriority   : %d\n", r.priority);
}

int main()
{
    int nr, choice, i, j;
    char searchID[10];

    printf("Enter the number of requests: ");
    scanf("%d",&nr);

    struct Request a[nr],temp;

    for (i = 0; i < nr; i++)
    {
        printf("\n--- Enter Request %d ---\n",i+1);

        printf("Request ID : ");
        scanf("%s", a[i].rid);

        printf("Location   : ");
        scanf("%s", a[i].loc);

        printf("People     : ");
        scanf("%d", &a[i].people);

        printf("Emergency (Critical/High/Medium/Low):");
        scanf("%s", a[i].emer);

        printf("Resources  : ");
        scanf("%s", a[i].res);

        printf("Status (Pending/Assigned/Completed): ");
        scanf("%s", a[i].status);

        strcpy(a[i].team, "Not Assigned");

        a[i].priority=getPriority(a[i].emer);
    }
    for (i=0;i<nr-1;i++)
    {
        for (j=i+1;j<nr;j++)
        {
            if (a[i].priority > a[j].priority)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    do
    {
        printf("\n\n===== EMERGENCY RESCUE SYSTEM =====");
        printf("\n1. Display Requests by Priority");
        printf("\n2. Assign Rescue Team");
        printf("\n3. Update Request Status");
        printf("\n4. Search Request");
        printf("\n5. Emergency Summary");
        printf("\n6. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\n--- Requests According to Priority ---\n");

                for (i=0;i<nr;i++)
                {
                    display(a[i]);
                }
                break;

            case 2:
                printf("\nEnter Request ID to assign team: ");
                scanf("%s", searchID);

                for (i=0;i<nr;i++)
                {
                    if (strcmp(a[i].rid,searchID)==0)
                    {
                        printf("Enter Rescue Team: ");
                        scanf("%s",a[i].team);

                        strcpy(a[i].status,"Assigned");

                        printf("\nRescue team assigned successfully.\n");
                        display(a[i]);
                        break;
                    }
                }

                if (i == nr)
                    printf("\nRequest not found.\n");

                break;

            case 3:
                printf("\nEnter Request ID: ");
                scanf("%s", searchID);

                for (i=0;i<nr;i++)
                {
                    if (strcmp(a[i].rid,searchID) == 0)
                    {
                        printf("Enter new status (Pending/Assigned/Completed): ");
                        scanf("%s", a[i].status);

                        printf("\nStatus updated successfully.\n");
                        display(a[i]);
                        break;
                    }
                }

                if (i == nr)
                    printf("\nRequest not found.\n");

                break;

            case 4:
                printf("\nEnter Request ID to search: ");
                scanf("%s", searchID);

                for (i=0;i<nr;i++)
                {
                    if (strcmp(a[i].rid, searchID) == 0)
                    {
                        printf("\n--- Request Found ---\n");
                        display(a[i]);
                        break;
                    }
                }

                if (i == nr)
                    printf("\nRequest not found.\n");

                break;

            case 5:
            {
                int critical=0,high=0,medium=0,low=0;
                int pending=0,assigned=0,completed=0;

                for (i=0;i<nr;i++)
                {
                    if (a[i].priority==1)
                        critical++;
                    else if (a[i].priority==2)
                        high++;
                    else if (a[i].priority==3)
                        medium++;
                    else
                        low++;

                    if (strcmp(a[i].status,"Pending") == 0)
                        pending++;
                    else if (strcmp(a[i].status,"Assigned") == 0)
                        assigned++;
                    else if (strcmp(a[i].status,"Completed") == 0)
                        completed++;
                }

                printf("\n--- EMERGENCY SUMMARY ---");
                printf("\nTotal Requests : %d",nr);

                printf("\n\nPriority-wise:");
                printf("\nCritical : %d", critical);
                printf("\nHigh     : %d", high);
                printf("\nMedium   : %d", medium);
                printf("\nLow      : %d", low);

                printf("\n\nStatus-wise:");
                printf("\nPending   : %d", pending);
                printf("\nAssigned  : %d", assigned);
                printf("\nCompleted : %d\n", completed);

                break;
            }

            case 6:
                printf("\nExiting Emergency Rescue System...\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}