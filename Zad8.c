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
Position AddRandom(Position,int);
int Preorder(Position);
int Inorder(Position);
int Postorder(Position);
int Levelorder(Position);
int Depth(Position);
int CurrentLevel(Position, int);
Position Delete(Position,int);
Position Find(Position);
int Replace(Position);

int main(){
    
    int first_root_value=0;
    int service_id=1000;
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
        "7 -replace the tree\n"
        "8 -randomly generated tree\n"
        "9 -exit program\n\n"
        "Your choice: \n");
        scanf("%d", &service_id);
        Menu(service_id,&Root);
    }
    return EXIT_SUCCESS;
}

Position Menu(int service_id, Position current){
    int new_value=0;
    int random_value=0;
    int number_of_nodes=0;
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
            Levelorder(current);
            return EXIT_SUCCESS;
            break;
        case 5:
            printf("\n\tKoji element zelis izbrisat? ");
            scanf(" %d", &new_value);
            Delete(current,new_value);
            return EXIT_SUCCESS;
            break;
        case 6:
            Find(current);
            return EXIT_SUCCESS;
            break;
        case 7:
            Replace(current);
            return EXIT_SUCCESS;
            break;
        case 8:
            printf("How many nodes do you want?\n");
            scanf("%d",&number_of_nodes);
            for(int j=0; j<number_of_nodes;j++){
                random_value=(rand()%90);
                if(random_value<10) continue;
                AddRandom(current, random_value);
            }
        case 9:
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

Position AddRandom(Position current, int random_value){
    if(current==NULL){
        return CreateNode(random_value);
    }
    else if(current->value>random_value){
        current->left=AddRandom(current->left,random_value);
    }
    else if(current->value<random_value){
        current->right=AddRandom(current->right,random_value);
    }
    return current;
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

int Levelorder(Position current){
    int depth = Depth(current);
    for (int i = depth; i > 0; i--)
        CurrentLevel(current, i);
}

int Depth(Position current){
    if (current == NULL)
        return EXIT_SUCCESS;
    else
    {
        int left_depth = Depth(current->left);
        int right_depth = Depth(current->right);

        if (left_depth > right_depth)
            return (left_depth + 1);
        else
            return (right_depth + 1);
    }
}

int CurrentLevel(Position current, int level){
    if (current == NULL)
        return EXIT_SUCCESS;
    if (level == 1)
        printf("%d ", current->value);
    else if (level > 1)
    {
        CurrentLevel(current->left, level - 1);
        CurrentLevel(current->right, level - 1);
    }
    return EXIT_SUCCESS;
}

Position Delete(Position current, int del_value){//3 different cases
    Position temporary_node=(Position)malloc(sizeof(Node));
    Position parent_node=(Position)malloc(sizeof(Node));
    Position next_node=(Position)malloc(sizeof(Node));
    if(current==NULL){
        return current;
    }
    if(current->value > del_value){
        current->left=Delete(current->left, del_value);
        return current;
    }
    if(current->value < del_value){
        current->right=Delete(current->right, del_value);
        return current;
    }
    //in previous steps we found node we want to delete, we located it so current is that node
    if(current->left==NULL){
        temporary_node=current->right;
        free(current);
        return temporary_node;
    }
    else if(current->right==NULL){
        temporary_node=root->left;
        free(current);
        return(temporary_node);
    }
    //lines above dealt with case of having one or none kids
    else{
        parent_node=current; //parent node is node with 2 kids
        next_node=current->right;
        while(next_node->left!=NULL){
            parent_node=next_node;
            next_node=next_node->left;
        }
        if(parent_node!=current){
            parent_node->left=next_node->right;
        }
        else{
            parent_node->right=next_node->right;
        }
        current->value = next_node->value;
        free(next_node);
        return(current);
        
    }
}


Position Find(Position current){
    int find_this_value = 0;
    printf("What value are you searching for?\n");
    scanf("%d",&find_this_value);
    while(current!=NULL){
        if(current->value==find_this_value){
            printf("Node with value %d is found!", find_this_value);
            return current;
        }
        if(current->value < find_this_value){
            current=current->right;
        }
        if(current->value > find_this_value){
            current=current->left;
        }
    }
}

int Replace(Position current){
    if(current==NULL){
        return 0;}
    else{
        return(current->value + Replace(current->left) + Replace(current->right));}
}
