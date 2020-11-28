#include <stdio.h>
#include <stdlib.h>

#define Red 1
#define Black 0

struct rbtree{
    struct rbtree *parent;
    struct rbtree *left;
    struct rbtree *right;
    int value;
    char color;
} typedef Tree;

int is_red ( Tree *node )
{
    return node != NULL && ((root->parent == NULL) && (root->left == NULL) && (root->right == NULL) && (root->color == Red));
}

/* функция для однократного поворота узла */
Tree *rb_single ( Tree *root, int dir )
{
    Tree *save;
    if (!dir) 
    {
        save = root->right;
        root->right = save->left;
        save->left = root;
    } else {
        save = root->left;
        root->left = save->right;
        save->right = root;
    }

    root->color = Red;
    save->color = Black;

    return save;
}

/* функция для двукратного поворота узла */
Tree *rb_double ( Tree *root, int dir )
{
    if (!dir) {
        root->right = rb_single ( root->right, !dir );
    } else {
        root->left = rb_single ( root->left, !dir );
    }
    return rb_single ( root, dir );
}

Tree *make_node (Tree *parent,  int data)
{
    Tree *node = (Tree *) malloc(sizeof(Tree));
    if (!node) {
        printf("Could`t allocate memory!\n");
        return NULL;
    }
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->value = data;
    node->color = Red;
    return node;
}

Tree *insert (Tree *root, int input){


    Tree head = {0}; /* временный корень дерева*/
    Tree *g, *t;     /* дедушка и родитель */
    Tree *p, *q;     /* родитель и итератор */
    int dir = 0, last;

    /* вспомогательные переменные */
    t = &head;
    g = p = NULL;
    q = t->right = root;

    if ((root->parent == NULL) && (root->left == NULL) && (root->right == NULL) && (root->color == Red))
    {
        root->value = input;
        root->color = Black;
    } else {
        while (true)
        {
            if (q == NULL) 
            {
                if (dir) {
                    p->right = q = make_node (p, input);
                } else {
                    p->left = q = make_node (p, input);
                }
                if (q == NULL)
                    return root;
            } else if (is_red(q->left) && is_red(q->right)) 
            {
                q->color = Red;
                q->left->color = Black;
                q->right->color = Black;
            }
            if (is_red(q) && is_red(p)) 
            {
                int dir2 = t->right == g;

                if (last){
                    if (q == p->right) 
                    {
                        if (dir2) 
                        {
                            t->right = rb_single(g, !last);
                        } else {
                            t->left = rb_single(g, !last);
                        }
                    } else {
                        if (dir2) 
                        {
                            t->right = rb_double(g, !last);
                        } else {
                            t->left = rb_double(g, !last);
                        }
                    }
                } else {
                    if ( q == p->left ) 
                    {
                        if (dir2) 
                        {
                            t->right = rb_single(g, !last);
                        } else {
                            t->left = rb_single(g, !last);
                        }
                    } else {
                        if (dir2) 
                        {
                            t->right = rb_double(g, !last);
                        } else {
                            t->left = rb_double(g, !last);
                        }
                    }
                }
            }
            
            if (q->value == input) 
            {
                break;
            }

            last = dir;
            dir = q->value < input;

            if (g != NULL)
                t = g;
            g = p, p = q;
            if (dir) 
            {
                q = q->right;
            } else {
                q = q->left;
            }
        }
        root = head.right;
    }
    root->color = Black;
    return root;
}

void draw(Tree *leaf, int depth)
{
    if (leaf->color) 
    {
        for (int i = 0; i < depth; ++i)
            printf("    ");
        printf("<%d>\n", leaf->value);
    } else {
        for (int i = 0; i < depth; ++i)
            printf("    ");
        printf("%d\n", leaf->value);
    }
}

void printing (Tree *leaf, int depth)
{
    if (leaf->right)
        printing(leaf->right, depth+1);
    draw(leaf, depth) ;
    if (leaf->left)
        printing(leaf->left, depth+1);
}

void show (Tree *root){
    if ((root->parent == NULL) && (root->left == NULL) && (root->right == NULL) && (root->color == Red)){
        printf("<Is Empty>\n");
        return;
    }
    int depth = 0;
    printing(root, depth);
}

Tree *delete(Tree *tree, int input )
{
    if ( tree != NULL )
    {
        Tree head = {0}; 
        Tree *q, *p, *g; 
        Tree *f = NULL;  
        int dir = 1;
        q = &head;
        g = p = NULL;
        q->right = tree;
        
        while ( dir ? (q->right != NULL) : (q->left != NULL)) {
            int last = dir;

            g = p, p = q;
            q = dir ? q->right : q->left;
            dir = q->value < input;

            if ( q->value == input )
                f = q;

            if ( !is_red ( q ) && !is_red ( dir ? q->right : q->left ) ) 
            {
                if ( is_red ( dir ? q->left : q->right ) ) 
                {
                    p = rb_single(q, dir);
                    if (last)
                    {
                        p->right = rb_single(q, dir);
                    } else {
                        p->left = rb_single(q, dir);
                    }
                } else if ( !is_red ( dir ? q->left : q->right ) )
                {
                    Tree *s = (!last ? p->right : p->left);


                    if ( s != NULL ) {
                        if ( !is_red ( !last ? s->right : s->left ) && !is_red ( last ? s->right : s->left ) ) 
                        {
                            p->color = Black;
                            s->color = Red;
                            q->color = Red;
                        }
                        else {
                            int dir2 = g->right == p;

                            if ( is_red ( last ? s->right : s->left ) ) 
                            {
                                if (dir2) {
                                    g->right = rb_double(p, last);
                                } else {
                                    g->left = rb_double(p, last);
                                }

                            } else if ( is_red ( !last ? s->right : s->left ) )
                            {
                                if (dir2) {
                                    g->right = rb_single ( p, last );
                                } else {
                                    g->left = rb_single ( p, last );
                                }
                            }

                            q->color = Red;
                            if (dir2) {
                                g->right->color = Red;
                                g->right->left->color = Black;
                                g->right->right->color = Black;
                            } else {
                                g->left->color = Red;
                                g->left->left->color = Black;
                                g->left->right->color = Black;
                            }
                        }
                    }
                }
            }
        }

        if ( f != NULL ) {
            f->value = q->value;
            if (p->right == q) {
                p->right =
                        ((q->left == NULL) ? q->right : q->left);
            } else {
                p->left =
                        ((q->left == NULL) ? q->right : q->left);
            }
            free ( q );
        }

        tree = head.right;
        if ( tree != NULL )
            tree->color = Black;
    }

    return tree;
}

void inorder(Tree *tree)
{
    if (tree->left)
        inorder(tree->left);
    printf("%d -> ", tree->value);
    if (tree->right)
        inorder(tree->right);
}

void preorder(Tree *tree)
{
    printf("%d -> ", tree->value);
    if (tree->left) 
    {
        preorder(tree->left);
    } else {
        printf(" Is empty");
    }
    if (tree->right)
        preorder(tree->right);
}

void postorder(Tree *tree)
{
    if (tree->left)
        postorder(tree->left);
    if (tree->right)
        postorder(tree->right);
    if (!( tree->right))
        printf("Is empty");
    printf("%d -> ", tree->value);
}

int main() 
{
    printf("Hello, World!\n");

    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if (!tree){
        printf("Could`t allocate memory!\n");
        return -1;
    }
    tree->parent = NULL;
    tree->left = NULL;
    tree->right = NULL;
    tree->color = Red;
    tree->value = 0;

    int choice = 0;
    int input = 0;
    do
    {
        printf("\nWhat do you want to do?\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch ( choice )
        {
            case 1:
                printf("\nEnter The Data for Inserting:");
                scanf("%d", &input);
                printf("\nInserting!\n\n");
                tree = insert(tree, input);
                break;
            case 2:
                printf("\nEnter The Data for Deleting:");
                scanf("%d", &input);
                tree = delete(tree, input);
                break;
            case 3:
                show(tree);
                break;
            case 4:
                printf("\n");
                if ((root->parent == NULL) && (root->left == NULL) && (root->right == NULL) && (root->color == Red))
                    inorder(baobab);
                printf("\n");
                break;
            case 5:
                printf("\n");
                if ((root->parent == NULL) && (root->left == NULL) && (root->right == NULL) && (root->color == Red))
                    preorder(tree);
                printf("\n");
                break;
            case 6:
                printf("\n");
                if ( (root->parent == NULL) && (root->left == NULL) && (root->right == NULL) && (root->color == Red) )
                {
                    if (tree->left)
                        postorder(tree->left);
                    if (tree->right)
                        postorder(tree->right);
                    printf("%d -> ", tree->value);
                }
                else
                {
                    printf("Is empty");
                }
                printf("\n");
                break;
            case 7:
                printf("\nExiting......");
                exit(1);
                return 0;
            default:
                printf("Please Enter a valid number!!\n");
                break;
        }
    }
    while (true);

    return 0;
}
