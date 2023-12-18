#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_CHAR 1024

struct node;
typedef struct node* Position;
typedef struct node{
    int value;
    Position left;
    Position right;
} Node;

Position Menu(int,Position);//we are returning Position cause we are always at some node, we must keep thrack of where during and after every action
Position CreateNode(int);
Position Add(Position,int);
int Preorder(Position);
int Inorder(Position);
int Postorder(Position);

int main(){
    
    int first_root_value=0;
    int service_id=8;
    Node Root={.value=0, .left=NULL, .right=NULL};
    
    printf("Hello ^^ welcome to binary tree! Please provide value for root node: \n");
    scanf("%d", &first_root_value);
    Root.value=first_root_value;
    
    while(service_id>=0){
        printf("Input one of the numbers to activate coresponding action:\n"
        "0 -add new node\n"
        "1 -preorder\n"
        "2 -inorder\n"
        "3 -postorder\n"
        "4 -levelorder\n"
        "5 -delete node\n"
        "6 -find node\n"
        "7 -exit program\n\n"
        "Your choice: \n");
        scanf("%d", &service_id);
        Menu(service_id,&Root);
    }
    return EXIT_SUCCESS;
}

Position Menu(int service_id, Position current){
    int new_value=0;
    switch(service_id){
        case 0:
            printf("New value?\n");
            scanf("%d",&new_value);
            Add(current,new_value);
            return EXIT_SUCCESS;
            break;
        case 1:
            Preorder(current);
            return EXIT_SUCCESS;
            break;
        case 2:
            Inorder(current); //aka Root
            return EXIT_SUCCESS;
            break;
        case 3:
            Postorder(current);
            return EXIT_SUCCESS;
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            exit(0);//exit(0) means successful ending of programs workings and tidy closing up of all streams and stuff
            break;
    }
}

Position CreateNode(int value){
    Position new_node=(Position)malloc(sizeof(Node));
    new_node->value=value;
    new_node->left=NULL;
    new_node->right=NULL;
    return new_node;
}

Position Add(Position current, int value){
    if(current==NULL){
        return CreateNode(value);
    }
    else if(current->value>value){
        current->left=Add(current->left,value);
    }
    else if(current->value<value){
        current->right=Add(current->right,value);
    }
    return current;//just in case nothing happens..?
}

int Preorder(Position current){
    if(current!=NULL){
        printf("\n%d\n",current->value);
        Preorder(current->left);
        Preorder(current->right);
    }
    return EXIT_SUCCESS;
}

int Inorder(Position current){
    if(current!=NULL){
        Inorder(current->left);
        printf("\n%d\n", current->value);
        Inorder(current->right);
    }
    return EXIT_SUCCESS;
}

int Postorder(Position current){
    if(current!=NULL){
        Postorder(current->left);
        Postorder(current->right);
        printf("\n%d\n",current->value);
    }
    return EXIT_SUCCESS;
}
