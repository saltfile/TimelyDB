

//#include <stdio.h>
//#include <stdlib.h>
//#include <cstring>
//#include <string>
//#include "rb_tree.h"
//#include "z_malloc.h"
#include "database_index.h"
#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

/**
 * 存入表的结构在map中
 */
void set_map_node(char* database_tablename,sql_operation* sql) {
    map_node.insert(pair<string, sql_operation* >(database_tablename, sql));    //把skip list放进map中 //pair是将2个数据组合成一组数据，当需要这样的需求时就可以使用pair
}
/**
 * 查找要插入数据的表的结构，生成Node,方便数据的插入
 */
sql_operation *get_map_node(char* database_tablename) {
    map<string , sql_operation *>::iterator iter;
    iter= map_node.find(database_tablename);
    if(iter != map_node.end())//判断是否为空
        return iter->second;
    return NULL;
}
/**
 * 初始化红黑树
 */
RBRoot *rbTree_init(char* database_tablename) {

    RBRoot *rbRoot;
    rbRoot = create_rbtree();

    rbtree_tableMap.insert(pair<string , RBRoot *>(database_tablename, rbRoot));    //把红黑树放进map中 //pair是将2个数据组合成一组数据，当需要这样的需求时就可以使用pair
    rbRoot->database_tablename = database_tablename;

    return rbRoot;
}
/**
 * 从map中查找红黑树
 * @param database_tablename
 * @return
 */
RBRoot *find_rbTree(char* database_tablename) {
    map<string , RBRoot *>::iterator iter;
    iter= rbtree_tableMap.find(database_tablename);
    if(iter != rbtree_tableMap.end())//判断是否为空
        return iter->second;
    return NULL;
}
/*
 * 创建红黑树，返回"红黑树的根"！
 */
RBRoot* create_rbtree()
{
    RBRoot *root =malloc_rb_root();
    root->node = NULL;
    root->rbhead= nullptr;

    return root;
}

/*
 * 前序遍历"红黑树"
 */
static void preorder(RBTree tree)
{
    if(tree != NULL)
    {
        printf("tag:%d \n", tree->tag_values->columnname);
        printf("values:%d \n", tree->tag_values->datalist->value);
        preorder(tree->left);
        preorder(tree->right);
    }
}
void preorder_rbtree(RBRoot *root)
{
    if (root)
        preorder(root->node);
}

/*
 * 中序遍历"红黑树"
 */
static void inorder(RBTree tree)
{
    if(tree != NULL)
    {
        inorder(tree->left);
        printf("tag:%d \n", tree->tag_values->columnname);
        printf("values:%d \n", tree->tag_values->datalist->value);
        inorder(tree->right);
    }
}

void inorder_rbtree(RBRoot *root)
{
    if (root)
        inorder(root->node);
}

/*
 * 后序遍历"红黑树"
 */
static void postorder(RBTree tree)
{
    if(tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        printf("tag:%d \n", tree->tag_values->columnname);
        printf("values:%d \n", tree->tag_values->datalist->value);
    }
}

void postorder_rbtree(RBRoot *root)
{
    if (root)
        postorder(root->node);
}

/*
 * (递归实现)查找"红黑树x"中键值为key的节点
 */
static rbtree_result_timestamp*  search(RBTree root, char* tag, char* dest, TokenType symbol, rbtree_result_timestamp* result)
{

    if (result==NULL) rbtree_result_timestamp* result;
    if (root == NULL) return result;


    switch (symbol) {
//                GE,                   //>=
//                GT,                   //>
//                EQ,                   //==
//                LE,                   //<=
//                LT,                   //<
        case Assignment: { //=
            //因为插入的时候，比较值的大小：小于在左边，大于等于在右边。
            //所以这里先比较值的大小，才比较tag是否相等
            //一种情况
            Node* find=root;
            //条件
            if (strcmp(dest ,(char *)find->tag_values->datalist->value) == 0) {

                if (strcmp(tag, find->tag_values->columnname) == 0) {
                    rbtree_result_timestamp*swap = malloc_rb_timestamp();
                    swap->timestamp = find->tag_values->datalist->timestamp;
                    swap->next=result;
                    result=swap;
                }
            }
            result=search(find->left,tag,dest,symbol,result);
            result=search(find->right,tag,dest,symbol,result);

            break;
        }
        case GT: {//>
            //两种情况：要查询的比根节点的小，左子树有一部分需要查，右子树都是
            // 要查询的比根节点的大，右子树部分是
            Node* find=root;
            //条件
            if (strcmp(dest ,(char *)find->tag_values->datalist->value) == -1) {

                if (strcmp(tag, find->tag_values->columnname) == 0) {
                    rbtree_result_timestamp*swap = malloc_rb_timestamp();
                    swap->timestamp = find->tag_values->datalist->timestamp;
                    swap->next=result;
                    result=swap;
                }
            }
            result=search(find->left,tag,dest,symbol,result);
            result=search(find->right,tag,dest,symbol,result);

            break;
        }
        case LT: {//<
            //两种情况：要查询的比根节点的小，左子树一部分是
            // 要查询的比根节点的大，左子树全都是，右子树一部分是

            Node* find=root;
            //条件
            if (strcmp(dest ,(char *)find->tag_values->datalist->value) == 1) {

                if (strcmp(tag, find->tag_values->columnname) == 0) {
                    rbtree_result_timestamp*swap = malloc_rb_timestamp();
                    swap->timestamp = find->tag_values->datalist->timestamp;
                    swap->next=result;
                    result=swap;
                }
            }
            result=search(find->left,tag,dest,symbol,result);
            result=search(find->right,tag,dest,symbol,result);

            break;

        }
        case GE: {//>=
            Node* find=root;
            //条件
            if (strcmp(dest ,(char *)find->tag_values->datalist->value) == -1 || strcmp(dest ,(char *)find->tag_values->datalist->value) == 0) {

                if (strcmp(tag, find->tag_values->columnname) == 0) {
                    rbtree_result_timestamp*swap = malloc_rb_timestamp();
                    swap->timestamp = find->tag_values->datalist->timestamp;
                    swap->next=result;
                    result=swap;
                }
            }
            result=search(find->left,tag,dest,symbol,result);
            result=search(find->right,tag,dest,symbol,result);

            break;
        }
        case LE: {//<=
            Node* find=root;
            //条件
            if (strcmp(dest ,(char *)find->tag_values->datalist->value) == 1 || strcmp(dest ,(char *)find->tag_values->datalist->value) == 0) {

                if (strcmp(tag, find->tag_values->columnname) == 0) {
                    rbtree_result_timestamp*swap = malloc_rb_timestamp();
                    swap->timestamp = find->tag_values->datalist->timestamp;
                    swap->next=result;
                    result=swap;
                }
            }
            result=search(find->left,tag,dest,symbol,result);
            result=search(find->right,tag,dest,symbol,result);

            break;
        }

    }
    return result;

}

rbtree_result_timestamp* rbtree_search(RBRoot *root, char* tag,char* dest,TokenType symbol)
{
    if (root)
        return search(root->node, tag,dest, symbol,NULL);
}


/*
 * 查找最小结点：返回tree为根结点的红黑树的最小结点。
 */
static Node* minimum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

int rbtree_minimum(RBRoot *root, char *val)
{
    Node *node;

    if (root)
        node = minimum(root->node);

    if (node == NULL)
        return -1;

    val = node->tag_values->columnname;
    return 0;
}

/*
 * 查找最大结点：返回tree为根结点的红黑树的最大结点。
 */
static Node* maximum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

int rbtree_maximum(RBRoot *root, char *val)
{
    Node *node;

    if (root)
        node = maximum(root->node);

    if (node == NULL)
        return -1;

    val = node->tag_values->columnname;
    return 0;
}

/*
 * 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
 */
static Node* rbtree_successor(RBTree x)
{
    // 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
    if (x->right != NULL)
        return minimum(x->right);

    // 如果x没有右孩子。则x有以下两种可能：
    // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
    // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/*
 * 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
 */
static Node* rbtree_predecessor(RBTree x)
{
    // 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
    if (x->left != NULL)
        return maximum(x->left);

    // 如果x没有左孩子。则x有以下两种可能：
    // (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
    // (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */
static void rbtree_left_rotate(RBRoot *root, Node *x)
{
    // 设置x的右孩子为y
    Node *y = x->right;

    // 将 “y的左孩子” 设为 “x的右孩子”；
    // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // 将 “x的父亲” 设为 “y的父亲”
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        //tree = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
        root->node = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        else
            x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
    }

    // 将 “x” 设为 “y的左孩子”
    y->left = x;
    // 将 “x的父节点” 设为 “y”
    x->parent = y;
}

/*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
    // 设置x是当前节点的左孩子。
    Node *x = y->left;

    // 将 “x的右孩子” 设为 “y的左孩子”；
    // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // 将 “y的父亲” 设为 “x的父亲”
    x->parent = y->parent;

    if (y->parent == NULL)
    {
        //tree = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
        root->node = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        else
            y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
    }

    // 将 “y” 设为 “x的右孩子”
    x->right = y;

    // 将 “y的父节点” 设为 “x”
    y->parent = x;
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
    Node *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                Node *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        }
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                Node *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }

    // 将根节点设为黑色
    rb_set_black(root->node);
}
///////////////////////////////////////////////////////////////////////////
/*
 * 添加节点：将节点(node)插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点
 */
static Node* insert(RBTreeNode * rbnode,Node* node){

    Node *y = NULL;
    Node *x = rbnode;


    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if (strcmp((char *)node->tag_values->datalist->value,(char *)x->tag_values->datalist->value)==-1){
            x=x->left;
        }else{
            x=x->right;
        }

    }


    rb_parent(node) = y;

    if (y != NULL)
    {
        if (strcmp((char *)node->tag_values->datalist->value, (char *)y->tag_values->datalist->value)==-1)
            y->left = node;                // 情况2：若“node所包含的值” < “y所包含的值”，则将node设为“y的左孩子”
        else
            y->right = node;            // 情况3：(“node所包含的值” >= “y所包含的值”)将node设为“y的右孩子”
    }
    else
    {
        rbnode = node;                // 情况1：若y是空节点，则将node设为根
    }

    // 2. 设置节点的颜色为红色
    node->color = RED;
    return rbnode;
}
void rbtree_insert(RBRoot *root, Node *node)
{
    Node* b=node;
    Node *a=NULL;

    while(b->tag_values->columnname!=NULL) {

        if (strcmp(b->tag_values->columnname,"timestamp")==0){
            b->tag_values=b->tag_values->nextcolumn;//指向下一列
            continue;
        }
        a=malloc_rb_node();
        a->tag_values->columnname=b->tag_values->columnname;
        a->tag_values->datalist->value=b->tag_values->datalist->value;
        a->tag_values->datalist->timestamp=b->tag_values->datalist->timestamp;
        a->tag_values->nextcolumn= nullptr; //把这一列隔离出来

        if (a) {
            root->node=insert(root->node, a);

        }
        // 3. 将它重新修正为一颗二叉查找树
        rbtree_insert_fixup(root, node);
        b->tag_values=b->tag_values->nextcolumn;//指向下一列
    }

    free(node);
}

/*
 * 创建结点
 *
 * 参数说明：
 *     key 是键值。
 *     parent 是父结点。
 *     left 是左孩子。
 *     right 是右孩子。
 */
static Node* create_rbtree_node(tuple_column* node, Node *parent, Node *left, Node* right)
{

    Node* p;

    if ((p =malloc_rb_node()) == NULL)
        return NULL;
    p->tag_values = node;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK; // 默认为黑色

    return p;
}


/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
 */
static void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent)
{
    Node *other;

    while ((!node || rb_is_black(node)) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

Node *delete_search(Node *root, condition* sql){
    Node *node= nullptr;

    condition* sql_data=sql;
    if (node!=NULL) return node;


    switch (sql_data->c_symbol) {
//                GE,                   //>=
//                GT,                   //>
//                EQ,                   //==
//                LE,                   //<=
//                LT,                   //<
        case Assignment: { //=
            //因为插入的时候，比较值的大小：小于在左边，大于等于在右边。
            //所以这里先比较值的大小，才比较tag是否相等
            //一种情况
            Node* find=root;
            //条件
            if (strcmp(sql_data->c_value ,find->tag_values->datalist->value) == 0) {
                if (strcmp(sql_data->c_name, find->tag_values->columnname) == 0)
                    node=find;
                return node;
            }
            find=delete_search(find->left, sql);
            find=delete_search(find->right, sql);

            break;
        }
        case GT: {//>
            //两种情况：要查询的比根节点的小，左子树有一部分需要查，右子树都是
            // 要查询的比根节点的大，右子树部分是
            Node* find=root;
            //条件
            if (strcmp(sql_data->c_value ,find->tag_values->datalist->value) == -1) {
                if (strcmp(sql_data->c_name, find->tag_values->columnname) == 0)
                    node=find;
                return node;
            }
            find=delete_search(find->left, sql);
            find=delete_search(find->right, sql);

            break;
        }
        case LT: {//<
            //两种情况：要查询的比根节点的小，左子树一部分是
            // 要查询的比根节点的大，左子树全都是，右子树一部分是

            Node* find=root;
            //条件
            if (strcmp(sql_data->c_value ,find->tag_values->datalist->value) == 1) {
                if (strcmp(sql_data->c_name, find->tag_values->columnname) == 0)
                    node=find;
                return node;
            }
            find=delete_search(find->left, sql);
            find=delete_search(find->right, sql);

            break;

        }
        case GE: {//>=
            Node* find=root;
            //条件
            if (strcmp(sql_data->c_value ,find->tag_values->datalist->value) == -1 || strcmp(sql_data->c_value ,find->tag_values->datalist->value) == 0) {
                if (strcmp(sql_data->c_name, find->tag_values->columnname) == 0)
                    node=find;
                return node;
            }
            find=delete_search(find->left, sql);
            find=delete_search(find->right, sql);

            break;
        }
        case LE: {//<=
            Node* find=root;
            //条件
            if (strcmp(sql_data->c_value ,find->tag_values->datalist->value) == 1 || strcmp(sql_data->c_value ,find->tag_values->datalist->value) == 0) {
                if (strcmp(sql_data->c_name, find->tag_values->columnname) == 0)
                    node=find;
                return node;
            }
            find=delete_search(find->left, sql);
            find=delete_search(find->right, sql);

            break;
        }

    }

    return node;
}
/*
 * 删除结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     node 删除的结点
 */
void rbtree_delete(RBRoot *root,sql_operation* sql)
{
    Node *child, *parent;
    int color;
    Node *node= nullptr;
    condition* swap=sql->data_list;
    condition* swap1=sql->data_list->next;
    swap->next= nullptr;
//    while(swap!=NULL){
    node= delete_search(root->node,swap);
    swap=swap1;
//    }

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) )
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        Node *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        }
        else
            // "node节点"是根节点，更新根节点。
            root->node = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = rb_parent(replace);
        // 保存"取代节点"的颜色
        color = rb_color(replace);

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            // child不为空
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            rbtree_delete_fixup(root, child, parent);
        free(node);

        return ;
    }

    if (node->left !=NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if (color == BLACK)
        rbtree_delete_fixup(root, child, parent);
    free(node);
}

/*
 * 删除键值为key的结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 键值
 */
//void delete_rbtree(RBRoot *root, Type key)
//{
//    Node *z, *node;
//
//    if ((z = search(root->node, key,NULL,NULL,NULL)) != NULL)
//        rbtree_delete(root, z);
//}

/*
 * 销毁红黑树
 */
static void rbtree_destroy(RBTree tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        rbtree_destroy(tree->left);
    if (tree->right != NULL)
        rbtree_destroy(tree->right);

    free(tree);
}

void destroy_rbtree(RBRoot *root)
{

    if (root != NULL)
        rbtree_destroy(root->node);

    free(root);
}

/*
 * 打印"红黑树"
 *
 * tree       -- 红黑树的节点
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
static void rbtree_print(RBTree tree, tuple_column* tag_values, int direction)
{
    if(tree != NULL)
    {
        if(direction==0) {    // tree是根节点
            printf("%2d(B) is root\n", tree->tag_values->columnname);
            printf("%2d(B) is root\n", tree->tag_values->datalist->value);
        }
        else                // tree是分支节点
            printf("%2d(%s) is %2d's %6s child\n",  tree->tag_values->columnname, rb_is_red(tree)?"R":"B", tree->tag_values->datalist->value, direction==1?"right" : "left");

        rbtree_print(tree->left, tree->tag_values->nextcolumn, -1);
        rbtree_print(tree->right,tree->tag_values->nextcolumn,  1);
    }
}

void print_rbtree(RBRoot *root)
{
    if (root!=NULL && root->node!=NULL)
        rbtree_print(root->node, root->node->tag_values, 0);
}