#include <stdio.h>
#include <string.h>

struct Patient
{
    char id[10], name[30], condition[50];
    int age, priority;
    char status[20], doctor[30], bed[10];
};

void display(struct Patient p)
{
    printf("\nID: %s", p.id);
    printf("\nName: %s", p.name); 
    printf("\nAge: %d", p.age);
    printf("\nCondition: %s", p.condition);
    printf("\nPriority: %d", p.priority);
    printf("\nStatus: %s",p.status);
    printf("\nDoctor: %s", p.doctor);
    printf("\nBed: %s", p.bed);
}

int main()
{
    struct Patient p[50], temp;
    int n, i, j, ch;
    char id[10];

    printf("Enter number of patients: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nPatient ID: ");
        scanf("%9s", p[i].id);
        printf("\nName: ");
        scanf("%29s", p[i].name);
        printf("\nAge: ");
        scanf("%d", &p[i].age);
        printf("\nCondition: ");
        scanf(" %49s", p[i].condition);
        printf("\nPriority (1-Critical, 2-High, 3-Medium, 4-Low): ");
        scanf("%d", &p[i].priority);

        strcpy(p[i].status, "Waiting");
        strcpy(p[i].doctor, "None");
        strcpy(p[i].bed, "None");
    }

    do
    {
        printf("\n\n1.Display  2.Sort Priority  3.Call Next Patient");
        printf("\n4.Assign Doctor/Bed  5.Update Status");
        printf("\n6.Search  7.Waiting Patients  8.Summary  9.Exit");
        printf("\nChoice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            for (i = 0; i < n; i++)
                display(p[i]);
            break;

        case 2:
            for (i = 0; i < n - 1; i++)
                for (j = i + 1; j < n; j++)
                    if (p[i].priority > p[j].priority)
                    {
                        temp = p[i];
                        p[i] = p[j];
                        p[j] = temp;
                    }

            for (i = 0; i < n; i++)
                display(p[i]);
            break;

        case 3:
            for (i = 0; i < n - 1; i++)
                for (j = i + 1; j < n; j++)
                    if (p[i].priority > p[j].priority)
                    {
                        temp = p[i];
                        p[i] = p[j];
                        p[j] = temp;
                    }

            for (i = 0; i < n; i++)
                if (strcmp(p[i].status, "Waiting") == 0)
                {
                    display(p[i]);
                    strcpy(p[i].status, "InTreatment");
                    break;
                }

            if (i == n)
                printf("No waiting patients.\n");
            break;

        case 4:
        case 5:
        case 6:
            printf("Enter Patient ID: ");
            scanf("%9s", id);

            for (i = 0; i < n; i++)
                if (strcmp(p[i].id, id) == 0)
                {
                    if (ch == 4)
                    {
                        printf("Doctor name: ");
                        scanf("%29s", p[i].doctor);
                        printf("Bed number: ");
                        scanf("%9s", p[i].bed);
                        strcpy(p[i].status, "InTreatment");
                    }
                    else if (ch == 5)
                    {
                        printf("Status (Waiting/InTreatment/Discharged): ");
                        scanf("%19s", p[i].status);
                    }

                    display(p[i]);
                    break;
                }

            if (i == n)
                printf("Patient not found.\n");
            break;

        case 7:
            for (i = 0; i < n; i++)
                if (strcmp(p[i].status, "Waiting") == 0)
                    display(p[i]);
            break;

        case 8:
        {
            int waiting = 0, treatment = 0, discharged = 0;
            int critical = 0, high = 0, medium = 0, low = 0;

            for (i = 0; i < n; i++)
            {
                if (p[i].priority == 1) critical++;
                else if (p[i].priority == 2) high++;
                else if (p[i].priority == 3) medium++;
                else if (p[i].priority == 4) low++;

                if (strcmp(p[i].status, "Waiting") == 0) waiting++;
                else if (strcmp(p[i].status, "InTreatment") == 0) treatment++;
                else if (strcmp(p[i].status, "Discharged") == 0) discharged++;
            }

            printf("\nTotal: %d\nCritical: %d\nHigh: %d\nMedium: %d\nLow: %d",
                   n, critical, high, medium, low);
            printf("\nWaiting: %d\nIn Treatment: %d\nDischarged: %d\n",
                   waiting, treatment, discharged);
            break;
        }

        case 9:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (ch != 9);

    return 0;
}