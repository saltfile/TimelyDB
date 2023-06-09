#include "_startup.h"













//
int main() {

    tylist_node *tyus = (tylist_node*) malloc(sizeof (tylist_node)) ;
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
//        tylist_node *tyus4 = (tylist_node*) malloc(sizeof (tylist_node));
//    tylist_node *p = NULL;
//    LIST_ADD_TAIL(tyus,p,tyus4)
//    LIST_LAST(pos,tyus);
tylink_list<int> *a =new tylink_list<int>(2);
    tylist_node *p = NULL;
    tylist_node *o = &a->list;
    LIST_ADD_TAIL(tyus,p,o);
//((class duty_node*)((char *)(p)-(unsigned long )(&((duty_node *)0)->list))); head type pos
//    ((typeof(tylink_list<int>) *)((char *)(p)-(unsigned long )(&((typeof(tylink_list<int>)*)0)->list)));
p = tyus->next;
tylink_list<int> *b = CONTAINER_OF(b,tylink_list<int>,p);
cout<<b->get_data();

    return 1;
}
