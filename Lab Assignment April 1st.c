#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char first_name[50], last_name[50];
    int roll_number;
    float cgpa;
    struct node* next;
}Student;

Student* findMid(Student* list) {
    Student* slow = list, *fast = list;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Student* merge(Student* left, Student* right){
    Student* res = NULL;
    Student* temp = res;

    while(left != NULL && right != NULL){
        if(strcmp(left->first_name, right->first_name) == -1){
            Student* newNode = (Student*) malloc(sizeof(Student));
            strcpy(newNode->first_name, left->first_name);
            strcpy(newNode->last_name, left->last_name);
            newNode->roll_number = left->roll_number;
            newNode->cgpa = left->cgpa;
            newNode->next = NULL;
            if(res == NULL){
                res = newNode;
                continue;
            }
            temp->next = newNode;
            temp = temp->next;
            left = left->next;
        }
        else if(strcmp(left->first_name, right->first_name) == 1){
            Student* newNode = (Student*) malloc(sizeof(Student));
            strcpy(newNode->first_name, right->first_name);
            strcpy(newNode->last_name, right->last_name);
            newNode->roll_number = right->roll_number;
            newNode->cgpa = right->cgpa;
            newNode->next = NULL;
            if(res == NULL){
                res = newNode;
                continue;
            }
            temp->next = newNode;
            temp = temp->next;
            right = right->next;
        }
        else{
            if(strcmp(left->last_name, right->last_name) == -1){
                Student* newNode = (Student*) malloc(sizeof(Student));
                strcpy(newNode->first_name, left->first_name);
                strcpy(newNode->last_name, left->last_name);
                newNode->roll_number = left->roll_number;
                newNode->cgpa = left->cgpa;
                newNode->next = NULL;
                if(res == NULL){
                    res = newNode;
                    continue;
                }
                temp->next = newNode;
                temp = temp->next;
                left = left->next;
            }
            else if(strcmp(left->last_name, right->last_name) == 1){
                Student* newNode = (Student*) malloc(sizeof(Student));
                strcpy(newNode->first_name, right->first_name);
                strcpy(newNode->last_name, right->last_name);
                newNode->roll_number = right->roll_number;
                newNode->cgpa = right->cgpa;
                newNode->next = NULL;
                if(res == NULL){
                    res = newNode;
                    continue;
                }
                temp->next = newNode;
                temp = temp->next;
                right = right->next;
            }
            else{
                Student* newNode = (Student*) malloc(sizeof(Student));
                strcpy(newNode->first_name, left->first_name);
                strcpy(newNode->last_name, left->last_name);
                newNode->roll_number = left->roll_number;
                newNode->cgpa = left->cgpa;
                newNode->next = NULL;
                if(res == NULL){
                    res = newNode;
                    continue;
                }
                temp->next = newNode;
                temp = temp->next;
                left = left->next;
            }
        }
    }

    while(left != NULL){
        Student* newNode = (Student*) malloc(sizeof(Student));
        strcpy(newNode->first_name, left->first_name);
        strcpy(newNode->last_name, left->last_name);
        newNode->roll_number = left->roll_number;
        newNode->cgpa = left->cgpa;
        newNode->next = NULL;
        if(res == NULL){
            res = newNode;
            continue;
        }
        temp->next = newNode;
        temp = temp->next;
        left = left->next;
    }
    while(right != NULL){
        Student* newNode = (Student*) malloc(sizeof(Student));
        strcpy(newNode->first_name, right->first_name);
        strcpy(newNode->last_name, right->last_name);
        newNode->roll_number = right->roll_number;
        newNode->cgpa = right->cgpa;
        newNode->next = NULL;
        if(res == NULL){
            res = newNode;
            continue;
        }
        temp->next = newNode;
        temp = temp->next;
        right = right->next;
    }

    return res;
}

Student* mergeSort(Student* list){
    if(list == NULL || list->next == NULL){
        return list;
    }
    Student* mid = findMid(list);
        Student* temp = mid->next;
        mid->next = NULL;
        mid = temp;

        Student* l = mergeSort(list);
        Student* r = mergeSort(mid);
        return merge(l, r);
}

Student* inputStudents(int n){
    Student* students = NULL, *temp = NULL;
    for(int i=0; i<n; i++){
        Student* newNode = (Student*) malloc(sizeof(Student));
        printf("Enter details of student %d (FirstName LastName RollNumber CGPA): ", i+1);
        scanf("%s %s %d %f", newNode->first_name, newNode->last_name, &newNode->roll_number, &newNode->cgpa);
        newNode->next = NULL;

        if(students == NULL){
            students = newNode;
        }
        else{
            temp->next = newNode;
        }
        temp = newNode;
    }

    return students;
}

void printStudents(Student* students, int n){
    printf("Sorted list of Students:\n");
    
    Student* temp = students;
    for(int i=0; i<n; i++){
        printf("%s %s %d %.1f\n", temp->first_name, temp->last_name, temp->roll_number, temp->cgpa);
        temp = temp->next;
    }
}

void freeStudents(Student* students) {
    while (students != NULL) {
        Student* temp = students;
        students = students->next;
        free(temp);
    }
}

int main(){
    Student* s_list = NULL;

    int N;
    printf("Enter no. of students: ");
    scanf("%d", &N);

    s_list = inputStudents(N);

    Student* sorted = mergeSort(s_list);
    printStudents(sorted, N);

    freeStudents(sorted);
    return 0;
}