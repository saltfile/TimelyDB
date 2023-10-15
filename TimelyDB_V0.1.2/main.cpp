#include "_startup.h"


//
int main() {


//    tylist_node *tyus = (tylist_node*) malloc(sizeof (tylist_node)) ;
//
//    tylist_node *tyus1 = (tylist_node*) malloc(sizeof (tylist_node));
//    tylist_node *tyus2 = (tylist_node*) malloc(sizeof (tylist_node));
//    tylist_node *tyus3 = (tylist_node*) malloc(sizeof (tylist_node));
//
//    tyus->next = tyus1;
//    tyus1->next = tyus2;
//    tyus2->next = tyus3;
//    tylist_node *pos = NULL;
//
//    LIST_LAST(pos,tyus);
//
//    tylist_node *tyus4 = (tylist_node*) malloc(sizeof (tylist_node));
//    tylist_node *p = NULL;
//    LIST_ADD_TAIL(tyus,p,tyus4)
//    LIST_LAST(pos,tyus);

    arr_list *ptr = (arr_list *) malloc(sizeof(arr_list));
    memset(ptr, 0, sizeof(arr_list));
    ptr->initialization();
    int *a = (int *) malloc(sizeof(int));
    int *b = (int *) malloc(sizeof(int));
    int *c = (int *) malloc(sizeof(int));
    int *d = (int *) malloc(sizeof(int));
    a = (int *) 1;
    b = (int *) 2;
    c = (int *) 3;
    d = (int *) 4;

    ptr->arr_list_add(1);
    ptr->arr_list_add(2);
    ptr->arr_list_add(3);


    tylist_node *p = ptr->get(2);

    collection *temp = ((struct collection *) ((char *) (p) - (unsigned long) (&((struct collection *) 0)->list)));
    int asf =  *((int*)temp->data);

    return 1;
}
