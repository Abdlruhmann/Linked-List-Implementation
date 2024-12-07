#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ***** STUDENT STRUCT ***** //
struct student {
    int id ;
    char name[30];
    int grade;
};
// to return in search if id not found
struct student default_student = { .id = -1 };

struct student fill_student() {

    struct student std1 ;
    printf("Enter id of the student: \n");
    scanf("%d", &std1.id);

    printf("Enter name of the student: \n");
    scanf("%s",std1.name);

    printf("Enter the grade of the student: \n");
    scanf("%d",&std1.grade);

    return std1;
}
void print_student(struct student std) {
    printf("Student id : %d\n", std.id);
    printf("Student name : %s\n", std.name);
    printf("Student grade : %d\n",std.grade);
}
// ***** STUDENT STRUCT END ***** //

// ***** NODE STRUCT ***** //
struct Node {
    struct student data;
    struct Node * next;
    struct Node * prev;
};
struct Node * head;
struct Node * tail;

// Create Node
struct Node * CreateNode(struct student data) {
    struct Node * ptr;
    ptr = (struct Node *)malloc(sizeof(struct Node));
    if(ptr) {
        ptr->data = data ;
        ptr->next = NULL;
        ptr->prev = NULL;
    }
    return ptr;
};

// Add Node
int AddNode(struct student data) {

    int retval = 0;
    struct Node * ptr;
    ptr = CreateNode(data);
    if(ptr) {
        retval = 1;
        if(!head) {
            head = tail = ptr;
        }else {
            tail->next = ptr;
            ptr->prev = tail;
            tail = ptr;
        }
    }
    return retval;
}

// SEARCH BY ID
struct student Search_By_ID(int id) {
    struct Node * curr ;
    struct student std ;
    curr = head ;
    while(curr != NULL && curr->data.id != id ) {
        curr = curr->next;
    }
    if(!curr) {
        std = default_student;
    }else{
        std = curr->data;
    }
    return std;
};

// SEARCH BY NAME
struct student Search_By_Name(char * name) {
    struct Node * curr ;
    struct student std ;
    curr = head;
    while( curr!= NULL && strcmp(curr->data.name, name) != 0) {
        curr = curr->next;
    }
     if(!curr) {
        std = default_student;
    }else{
        std = curr->data;
    }
    return std;
};

// PRINT LIST
void Print_List(void) {
    if(!head){
        printf("List is Empty!");
    }
    struct Node * curr;
    curr = head ;
    int i= 0;
    while(curr) {
        printf("-------- %d --------\n",i+1);
        print_student(curr->data);
        curr = curr->next;
        i++;
        printf("--------------------\n");
    }
}

// FREE LIST
void Free_List(void) {
    struct Node * curr ;
    while(head) {
        curr = head;
        head = head->next;
        printf("Deleting Node of student id : %d\n", curr->data.id);
        free(curr);
    }
    tail=NULL;
    return;
}


// Insert
int Insert(struct student data, int location) {
    int retval = 0 ;
    // create node with user data
    struct Node * ptr ;
    struct Node * temp;
    ptr = CreateNode(data);

    if(ptr){
        retval = 1;
        if(!head) {
            head = tail = ptr;
        }else {
            if(location == 0)  { //first node
                ptr->next=head;
                head->prev=ptr;
                head=ptr;
            }else{
                 //1) find the node of location -1
                 temp =head;
                 for(int i = 0 ; i < location - 1 ; i++) {
                    temp = temp->next;
                 }
                 if(temp == tail || temp == NULL)  { //last node
                    tail->next = ptr;
                    ptr->prev = tail;
                    tail = ptr;
                 }else { //middle
                     //2) ptr->next = node->next
                     ptr->next = temp->next;
                    //3) node->next->prev = ptr
                    temp->next->prev = ptr;
                    //4) node->next = ptr
                    temp->next = ptr;
                    //5) ptr->prev = node
                    ptr->prev = temp;
                }
            }
        }
    }
    return retval;
};

// Delete
int Delete_From_List(int location) {
    int retval=0;
    struct Node * temp;

    if(!head) {
        printf("List is Empty!");
        retval=0;
    }else {
        if(location == 0) { // first node
            if(head->next == NULL) { // only one node
                printf("Deleting Node of student : %s\n", head->data.name);
                free(head);
                head=tail=NULL;
                retval=1;
            }else { // more than one
                temp = head;
                head = head->next;
                head->prev = NULL;
                printf("Deleting Node of student : %s\n", temp->data.name);
                free(temp);
                retval = 1;
            }
        } else {
            temp = head;
            for(int i = 0 ; i < location ; i++) {
                temp=temp->next;
                if(temp == NULL) { // no node to delete
                    retval=0;
                }
            }
            if(temp == tail) { // last node
                tail=temp->prev;
                temp->prev->next=NULL;
                printf("Deleting Node of student : %s\n", temp->data.name);
                free(temp);
                retval=1;
            }else { // node in the middle
                temp->next->prev=temp->prev;
                temp->prev->next=temp->next;
                printf("Deleting Node of student : %s\n", temp->data.name);
                free(temp);
                retval=1;
            }
        }
    }
    return retval;
};
// MENU
void Menu(void) {
printf("\n------ Menu ------\n");
printf("1. Add(end of list).\n");
printf("2. Insert.\n");
printf("3. Search By ID.\n");
printf("4. Search By Name.\n");
printf("5. Delete.\n");
printf("6. Free the list.\n");
printf("7. Print the list.\n");
printf("8. Exit.\n");
printf("----------------------\n");
}



int main()
{
    int running = 1 ;
    int choice;

    do {
        Menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                {
                    // add node
                    struct student std = fill_student();
                    int isadded = AddNode(std);
                    if(isadded) {
                        printf("_____OUTPUT_____\n");
                        printf("Student %s Added Successfully!\n", std.name);
                        printf("________________\n");
                    }else {
                        printf("_____OUTPUT_____\n");
                        printf("Error While Adding new student!\n");
                        printf("________________\n");
                    }
                    break;
                }

            case 2:
                {
                    //insert
                    int loc;
                    struct student std = fill_student();
                    printf("Now, Please provide location to insert: \n");
                    scanf("%d", &loc);
                    int isadded = Insert(std,loc);

                    if(isadded) {
                        printf("_____OUTPUT_____\n");
                        printf("Student %s Added Successfully!\n", std.name);
                        printf("________________\n");
                    }else {
                        printf("_____OUTPUT_____\n");
                        printf("Error While Adding new student!\n");
                        printf("________________\n");
                    }
                    break;
                }

            case 3:
                //search by id
                {
                    int input_id;
                    printf("PLease enter id to search: \n");
                    scanf("%d", &input_id);
                    //
                    struct student std = Search_By_ID(input_id);
                    if(std.id != -1) {
                        printf("_____OUTPUT_____\n");
                        printf("Found!--> Student id : %d  Student Name: %s\n",std.id,std.name);
                        printf("________________\n");
                    }else {
                        printf("_____OUTPUT_____\n");
                        printf("ID NOT Found!\n");
                        printf("________________\n");
                    }

                    break;
                }

            case 4:
                {
                    //search by name
                    char input_name[30];
                    struct student std ;

                    printf("Please enter a name to search: \n");
                    scanf("%s",input_name);
                    //
                    std = Search_By_Name(input_name);
                    if(std.id != -1) {
                        printf("_____OUTPUT_____\n");
                        printf("Found!--> Student id : %d  Student Name: %s\n",std.id,std.name);
                        printf("________________\n");
                    }else {
                        printf("_____OUTPUT_____\n");
                        printf("Name NOT Found!\n");
                        printf("________________\n");
                    }
                    break;
                }
            case 5: {
                //delete
                int ans;
                int loc;
                printf("Please enter a location to delete: \n");
                scanf("%d", &loc);
                printf("Are you sure want to delete node in location: %d ?\n",loc);
                printf("1.Yes\n");
                printf("2.Cancel\n");

                scanf("%d",&ans);
                switch(ans) {
                    case 1: {
                        int isDel=Delete_From_List(loc);
                        if(isDel) {
                            printf("_____OUTPUT_____\n");
                            printf("Deleted Successfully!\n");
                            printf("________________\n");
                        } else {
                            printf("_____OUTPUT_____\n");
                            printf("Error While Deleting the node!\n");
                            printf("________________\n");
                        }
                        break;
                    }
                    case 2: {
                        printf("Canceled!");
                        break;
                    }
                    default:
                    printf("Invalid Choice!");
                    break;
                }
                break;
            }
            case 6: {

                //free list
                int ans;
                printf("Are you sure want to free the list ?\n");
                printf("1.Yes\n");
                printf("2.Cancel\n");

                scanf("%d",&ans);
                switch(ans) {
                    case 1: {
                        printf("Freeing the list!\n");
                        Free_List();
                        printf("List is free now!\n");
                        break;
                    }
                    case 2: {
                        printf("Canceled!");
                        break;
                    }
                    default:
                    printf("_____OUTPUT_____\n");
                    printf("Invalid Choice!");
                    printf("________________\n");
                    break;
                }
                break;
            }
            case 7:
                //print list
                Print_List();
                break;
            case 8:
                printf("Exiting..");
                running = 0 ;
                break;
            default:
                printf("_____OUTPUT_____\n");
                printf("Invalid Choice!");
                printf("________________\n");
                break;
        }

    }while(running);
}
