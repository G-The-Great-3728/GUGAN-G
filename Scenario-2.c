#include <stdio.h>
#include <string.h>

struct Complaint
{
    char id[10];
    char category[30];
    char problem[100];
    char location[50];
    char priority[10];
    char status[20];
};

int pri(char p[])
{
    if (strcmp(p, "High") == 0)
        return 1;
    if (strcmp(p, "Medium") == 0)
        return 2;
    return 3;
}

void display(struct Complaint c)
{
    printf("\nID       : %s", c.id);
    printf("\nCategory : %s", c.category);
    printf("\nProblem  : %s", c.problem);
    printf("\nLocation : %s", c.location);
    printf("\nPriority : %s", c.priority);
    printf("\nStatus   : %s\n", c.status);
}

int main()
{
    int n, i, j, ch;
    char id[10], category[30];
    struct Complaint a[50], temp;

    printf("Enter number of complaints: ");
    scanf("%d", &n);

    /* Register complaints */
    for (i = 0; i < n; i++)
    {
        printf("\n--- Complaint %d ---\n", i + 1);

        printf("ID       : ");
        scanf("%s", a[i].id);

        printf("Category : ");
        scanf(" %[^\n]", a[i].category);

        printf("Problem  : ");
        scanf(" %[^\n]", a[i].problem);

        printf("Location : ");
        scanf(" %[^\n]", a[i].location);

        printf("Priority (High/Medium/Low): ");
        scanf("%s", a[i].priority);

        printf("Status (Pending/InProgress/Resolved): ");
        scanf("%s", a[i].status);
    }

    do
    {
        printf("\n\n===== SMART CAMPUS COMPLAINT SYSTEM =====");
        printf("\n1. Display All");
        printf("\n2. Pending Complaints");
        printf("\n3. Sort by Priority");
        printf("\n4. Search Complaint");
        printf("\n5. Update Status");
        printf("\n6. Filter by Category");
        printf("\n7. Summary");
        printf("\n8. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            for (i = 0; i < n; i++)
                display(a[i]);
            break;

        case 2:
            printf("\n--- Pending Complaints ---\n");
            for (i = 0; i < n; i++)
                if (strcmp(a[i].status, "Pending") == 0)
                    display(a[i]);
            break;

        case 3:
            for (i = 0; i < n - 1; i++)
                for (j = i + 1; j < n; j++)
                    if (pri(a[i].priority) > pri(a[j].priority))
                    {
                        temp = a[i];
                        a[i] = a[j];
                        a[j] = temp;
                    }

            printf("\n--- Complaints by Priority ---\n");
            for (i = 0; i < n; i++)
                display(a[i]);
            break;

        case 4:
            printf("Enter Complaint ID: ");
            scanf("%s", id);

            for (i = 0; i < n; i++)
                if (strcmp(a[i].id, id) == 0)
                {
                    display(a[i]);
                    break;
                }

            if (i == n)
                printf("Complaint not found.\n");
            break;

        case 5:
            printf("Enter Complaint ID: ");
            scanf("%s", id);

            for (i = 0; i < n; i++)
                if (strcmp(a[i].id, id) == 0)
                {
                    printf("Enter new status: ");
                    scanf("%s", a[i].status);
                    printf("Status updated.\n");
                    break;
                }

            if (i == n)
                printf("Complaint not found.\n");
            break;

        case 6:
            printf("Enter Category: ");
            scanf(" %[^\n]", category);

            for (i = 0; i < n; i++)
                if (strcmp(a[i].category, category) == 0)
                    display(a[i]);
            break;

        case 7:
        {
            int h = 0, m = 0, l = 0;
            int p = 0, ip = 0, r = 0;

            for (i = 0; i < n; i++)
            {
                if (strcmp(a[i].priority, "High") == 0) h++;
                else if (strcmp(a[i].priority, "Medium") == 0) m++;
                else l++;

                if (strcmp(a[i].status, "Pending") == 0) p++;
                else if (strcmp(a[i].status, "InProgress") == 0) ip++;
                else r++;
            }

            printf("\n--- SUMMARY ---");
            printf("\nTotal       : %d", n);
            printf("\nHigh        : %d", h);
            printf("\nMedium      : %d", m);
            printf("\nLow         : %d", l);
            printf("\nPending     : %d", p);
            printf("\nInProgress  : %d", ip);
            printf("\nResolved    : %d\n", r);
            break;
        }

        case 8:
            printf("\nExiting...\n");
            break;

        default:
            printf("\nInvalid choice.\n");
        }

    } while (ch != 8);

    return 0;
}