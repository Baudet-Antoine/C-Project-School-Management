#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int ID;
    char Name[50];
    char Program[50];
    float GPA;
};

struct Professor {
    int ID;
    char Name[50];
    char Department[50];
    struct Student SupervisedStudents[10];
};

void SaveData(struct Student *students, struct Professor *profs) {
    FILE *fs = fopen("students.dat", "wb");
    FILE *fp = fopen("professors.dat", "wb");

    if (fs && fp) {
        int i = 0;
        while (students[i].ID) i++;
        fwrite(students, sizeof(struct Student), i, fs);
        fclose(fs);

        i = 0;
        while (profs[i].ID) i++;
        fwrite(profs, sizeof(struct Professor), i, fp);
        fclose(fp);

        printf("Data saved successfully.\n");
    } else {
        printf("Error opening files for saving.\n");
    }
}

void LoadData(struct Student *students, struct Professor *profs) {
    FILE *fs = fopen("students.dat", "rb");
    FILE *fp = fopen("professors.dat", "rb");

    if (fs && fp) {
        int count = fread(students, sizeof(struct Student), 50, fs);
        students[count].ID = 0;  // Sentinelle de fin
        fclose(fs);

        count = fread(profs, sizeof(struct Professor), 50, fp);
        profs[count].ID = 0;
        fclose(fp);

        printf("Data loaded successfully.\n");
    } else {
        printf("Error opening files for loading (maybe first time running?).\n");
    }
}

void SortStudentsByGPA(struct Student *List) {
    int n = 0;
    while (List[n].ID) n++;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (List[j].GPA < List[j + 1].GPA) {
                struct Student temp = List[j];
                List[j] = List[j + 1];
                List[j + 1] = temp;
            }
        }
    }
}

void SortStudentsByProgram(struct Student *List) {
    int n = 0;
    while (List[n].ID) n++;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(List[j].Program, List[j + 1].Program) > 0) {
                struct Student temp = List[j];
                List[j] = List[j + 1];
                List[j + 1] = temp;
            }
        }
    }
}


void SearchStudentByID(struct Student *List, int ID) {
    int found = 0;
    int i = 0;
    while (List[i].ID) {
        if (List[i].ID == ID) {
            printf("_______________\n");
            printf("|Student ID : %d\n|Name : %s|Program : %s|GPA : %f\n",
                   List[i].ID, List[i].Name, List[i].Program, List[i].GPA);
            printf("---------------\n");
            found = 1;
            break;
        }
        i++;
    }
    if (!found) {
        printf("No student found with ID %d\n", ID);
    }
}

void ModifyStudent(struct Student *List, int index) {
    printf("Modifying Student ID %d:\n", List[index].ID);
    printf("Enter the new full name: ");
    fflush(stdin);
    fgets(List[index].Name, sizeof(List[index].Name), stdin);

    printf("Enter the new program: ");
    fflush(stdin);
    fgets(List[index].Program, sizeof(List[index].Program), stdin);

    printf("Enter the new GPA: ");
    scanf("%f", &List[index].GPA);

}

void DeleteStudent(struct Student *List, int index) {
    int i = index;
    while (List[i].ID) {
        List[i] = List[i + 1];
        i++;
    }
}

void AddNewStudent(struct Student *L) {

    int i = 0;
    while((*(L+i)).ID)
    {
        i++;
    }

    struct Student s;
    s.ID = i+1;
    printf("Enter the Student's full name");
    fflush(stdin);
    fgets(s.Name,sizeof(s.Name),stdin);
    printf("Enter the Student's Program");
    fflush(stdin);
    fgets(s.Program,sizeof(s.Program),stdin);
    printf("Enter the Student's GPA");
    scanf("%f",&s.GPA);

    *(L+i) = s;
}

void AddNewProfessor(struct Professor *P) {
    int i = 0;
    while((*(P+i)).ID)
    {
        i++;
    }

    struct Professor p;
    p.ID = i+1;
    printf("Enter the Professor's full name");
    fflush(stdin);
    fgets(p.Name,sizeof(p.Name),stdin);
    printf("Enter the Professor's Department");
    fflush(stdin);
    fgets(p.Department,sizeof(p.Department),stdin);

    *(P+i) = p;
}

void DisplayStudentList(struct Student List[]) {
    printf("Student List :\n");
    int x = 0;
    while (List[x].ID) {
        x++;
    }
    for (int i = 0 ; i < x; i++) {
        printf("_______________\n");
        printf("|Student ID : %d\n|Name : %s|Program : %s|GPA : %f\n",List[i].ID,List[i].Name,List[i].Program,List[i].GPA);
    }
    printf("---------------\n");
}

void DisplayStudentsFromProfessor(struct Professor List[],const int P) {
    printf("Students of %s : \n", List[P-1].Name);
    int x = 0;
    while (List[P-1].SupervisedStudents[x].ID) {
        x++;
    }
    for (int i = 0 ; i < x; i++) {
        printf("_______________\n");
        printf("|Student ID : %d\n|Name : %s|Program : %s|GPA : %f\n",List[P-1].SupervisedStudents[i].ID,List[P-1].SupervisedStudents[i].Name,List[P-1].SupervisedStudents[i].Program,List[P-1].SupervisedStudents[i].GPA);
    }
    printf("---------------\n");
}

void DisplayProfessorList(struct Professor List[]) {
    printf("Professor List :\n");
    int x = 0;
    while (List[x].ID) {
        x++;
    }
    for (int i = 0 ; i < x; i++) {
        printf("_______________\n");
        printf("|Professor ID : %d\n|Name : %s|Department : %s",List[i].ID,List[i].Name,List[i].Department);
    }
    printf("---------------\n");
}

void AddStudentToProfessor(struct Student *S,struct Professor *P) {
    printf("AAAAAAAAAAAAA%s",S->Name);
    printf("AAAAAAAAAAAA%s", P->Name);
    int x = 0;
    while (P->SupervisedStudents[x].ID) {
        x++;
    }
    P->SupervisedStudents[x] = *S;
}

void main() {
    struct Student StudentList[50] = {0};
    struct Professor ProfessorList[50] = {0};
    struct Professor *PtProfessorList = ProfessorList;
    struct Student *PtStudentList = StudentList;

    LoadData(StudentList, ProfessorList);

    int MenuChoice = 0;

    while (MenuChoice < 1 || MenuChoice > 3) {
        printf(" ----- MENU ----- \n"
            "1) Display Info\n"
            "2) Add new Data\n"
            "3) Other Features\n"
            "4) Save & Exit\n");
        scanf("%d",&MenuChoice);

        switch (MenuChoice) {
            case 1:
                MenuChoice = 0;
            while (MenuChoice < 1 ||MenuChoice > 3) {
                printf("What do you want to Display ?\n"
                   "1) Student list\n"
                   "2) Professor list\n"
                   "3) Students supervised by specific professor\n");
                scanf("%d",&MenuChoice);
            }
            switch (MenuChoice) {
                case 1:
                    DisplayStudentList(StudentList);
                break;
                case 2:
                    DisplayProfessorList(ProfessorList);
                break;
                default:
                    MenuChoice = 0;
                    int x = 0;
                    while (ProfessorList[x].ID) {
                        x++;
                    }
                    if (x == 0) {
                        printf("There are no professor\n");
                        break;
                    }
                    while (MenuChoice < 1 || MenuChoice > x) {
                        printf("Chose a professor from the list :\n");
                        DisplayProfessorList(ProfessorList);
                        scanf("%d",&MenuChoice);
                    }

                    DisplayStudentsFromProfessor(ProfessorList,MenuChoice);
                break;
            }
            break;
            case 2:
                MenuChoice = 0;
                while (MenuChoice < 1 ||MenuChoice > 2) {
                    printf("What do you want to Add ?\n"
                            "1) Professor\n"
                            "2) Student\n");
                    scanf("%d",&MenuChoice);
                }
                switch (MenuChoice) {
                    case 1:
                        AddNewProfessor(PtProfessorList);
                    break;
                    default:
                        AddNewStudent(PtStudentList);
                    break;
                }
            break;
            case 3:
                MenuChoice = 0;
                while (MenuChoice < 1 || MenuChoice > 4) {
                    printf("What other feature do you want to use ?\n"
                           "1) Add student to professor\n"
                           "2) Modify / delete student\n"
                           "3) Search student by ID\n"
                           "4) Sort Students");
                    scanf("%d",&MenuChoice);
                }
                switch (MenuChoice) {
                    case 1:
                        MenuChoice = 0;
                        int x = 0;
                        while (ProfessorList[x].ID) {
                            x++;
                        }
                        if (x == 0) {
                            printf("There are no professor\n");
                            break;
                        }
                        while (MenuChoice < 1 || MenuChoice > x) {
                            printf("Chose a professor from the list :\n");
                            DisplayProfessorList(ProfessorList);
                            scanf("%d",&MenuChoice);
                        }
                        x = MenuChoice;
                        MenuChoice = 0;
                        int z = 0;
                        while (StudentList[z].ID) {
                            z++;
                        }
                        if (z == 0) {
                            printf("There are no Student\n");
                            break;
                        }
                        while (MenuChoice < 1 || MenuChoice > z) {
                            printf("Chose a student from the list :\n");
                            DisplayStudentList(StudentList);
                            scanf("%d",&MenuChoice);
                        }

                        AddStudentToProfessor(&StudentList[x-1],&ProfessorList[MenuChoice-1]);

                        break;
                    case 2:
                        MenuChoice = 0;
                        z = 0;
                        while (StudentList[z].ID) {
                            z++;
                        }
                        if (z == 0) {
                            printf("There are no students.\n");
                            break;
                        }
                        while (MenuChoice < 1 || MenuChoice > z) {
                            printf("Choose a student from the list:\n");
                            DisplayStudentList(StudentList);
                            scanf("%d", &MenuChoice);
                        }
                        int selectedIndex = MenuChoice - 1;

                        MenuChoice = 0;
                        while (MenuChoice < 1 || MenuChoice > 2) {
                            printf("1) Modify student\n2) Delete student\n");
                            scanf("%d", &MenuChoice);
                        }
                        if (MenuChoice == 1) {
                            ModifyStudent(StudentList, selectedIndex);
                        } else {
                            DeleteStudent(StudentList, selectedIndex);
                        }
                        break;
                    case 3:
                        printf("Enter the Student ID to search: ");
                        int idToSearch;
                        scanf("%d", &idToSearch);
                        SearchStudentByID(StudentList, idToSearch);
                        break;
                    default:
                        MenuChoice = 0;
                        while (MenuChoice < 1 || MenuChoice > 2) {
                            printf("Sort students by:\n"
                                   "1) GPA (descending)\n"
                                   "2) Program (A to Z)\n");
                            scanf("%d", &MenuChoice);
                        }

                        if (MenuChoice == 1)
                            SortStudentsByGPA(StudentList);
                        else
                            SortStudentsByProgram(StudentList);

                        DisplayStudentList(StudentList);
                        break;
                }
                break;
            default:
                SaveData(StudentList, ProfessorList);
                printf("Goodbye!\n");
                exit(0);
            break;
        }
        MenuChoice = 0;
    }
}
