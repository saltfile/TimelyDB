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
    int*b = (int *) malloc(sizeof(int));
    memset(b,0, sizeof(b));
    int *c = (int *) malloc(sizeof(int));
    int *d = (int *) malloc(sizeof(int));


    int nud = 10;
    int nud1 = 11;
    int nud2 = 12;
    int nud3 = 13;

    a = &nud;
    c = &nud2;
    b = &nud1;
    d = &nud3;

    ptr->arr_list_add((void *)a);
    ptr->arr_list_add((void *)b);
    ptr->arr_list_add((void *)c);
    ptr->arr_list_add((void *)d);

    int *str =(int *)ptr->get(ptr->length-1);
    cout<<*str;
    ptr->arr_list_remove(ptr->length-1);
    int *sty = (int *)ptr->get(ptr->length-1);
    cout<<*sty;

//    collection *temp = ((struct collection *) ((char *) (p) - (unsigned long) (&((struct collection *) 0)->list)));
//    char *asf = (char*)temp->data;
//    cout<<asf<<endl;



    return 1;
}
