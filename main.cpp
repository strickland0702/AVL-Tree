#include <iostream>

using namespace std;

struct Item{
    int key;
};

struct node {
    Item item;
    int height;
    node *left;
    node *right;
};

int max(int a, int b){
    if (a > b) return a;
    else return b;
}

int Height(node *n){
    if (!n) return -1;
    else return n->height;
}

void AdjustHeight(node *n){
    if (!n) return;

    n->height = max(Height(n->left), Height(n->right)) + 1;
}

int Balfactor(node *n){
    if (!n) return 0;
    return (Height(n->left) - Height(n->right));
}

node *LLRotation(node *&n){
    node *temp = n->left;
    n->left = temp->right;
    temp->right = n;
    AdjustHeight(temp);
    AdjustHeight(n);
    return temp;
}

node *RRRotation(node *&n){
    node *temp = n->right;
    n->right = temp->left;
    temp->left = n;
    AdjustHeight(temp);
    AdjustHeight(n);
    return temp;
}

node *LRRotation(node *&n){
    n->left = RRRotation(n->left);
    return LLRotation(n);
}

node *RLRotation(node *&n){
    n->right = LLRotation(n->right);
    return  RRRotation(n);
}

node *Balance(node *&n){
    if (Balfactor(n) > 1){
        if (Balfactor(n->left) > 0) n = LLRotation(n);
        else n = LRRotation(n);
    }
    else if(Balfactor(n) < -1){
        if(Balfactor(n->right) < 0) n = RRRotation(n);
        else n = RLRotation(n);
    }

    return n;
}

void insert(node *&root, Item item){
    if (root == NULL){
        root = new node;
        root->item = item;
        root->left = root->right = NULL;
        root->height = 0;
    }

    if (item.key < root->item.key) insert(root->left, item);
    else if (item.key > root->item.key) insert(root->right, item);

    //每一个子插入都会保持平衡
    root = Balance(root);
    AdjustHeight(root);
}

void in_order(node *n){
    if (n == NULL) return;

    in_order(n->left);
    cout << n->item.key << "(" << n->height << ")";
    in_order(n->right);
}

int main() {

    node *root = NULL;
    int insert_keys[7] = {6, 8, 5, 3, 2, 1, 0};

    Item items[7];
    for (int i=0;i<7;i++){
        items[i].key = insert_keys[i];
        insert(root, items[i]);
    }

    in_order(root);
    return 0;

}