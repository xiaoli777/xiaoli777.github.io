#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class elemType>
struct binaryTreeNode
{
    elemType info;
    binaryTreeNode<elemType> *left;
    binaryTreeNode<elemType> *right;
};

template <class elemType>
int height(binaryTreeNode<elemType> *btn)
{
    if (btn == NULL)
        return 0;
    else
        return 1 + max(height(btn->left), height(btn->right));
}

template <class elemType>
void copyTree(binaryTreeNode<elemType>* &copiedTreeRoot,
		binaryTreeNode<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == NULL) {
        copiedTreeRoot = NULL;
    }
    else {
        copiedTreeRoot = new binaryTreeNode<elemType>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

//前序遍历
template <class elemType>
void preorder(binaryTreeNode<elemType> *btn)
{
    if (btn == NULL)  return;
    cout << btn->info << " ";
    preorder(btn->left);
    preorder(btn->right);
}

//中序遍历
template <class elemType>
void inorder(binaryTreeNode<elemType> *btn)
{
    if (btn == NULL)  return;
    inorder(btn->left);
    cout << btn->info << " ";
    inorder(btn->right);
}

//后序遍历
template <class elemType>
void postorder(binaryTreeNode<elemType> *btn)
{
    if (btn == NULL)  return;
    postorder(btn->left);
    postorder(btn->right);
    cout << btn->info << " ";
}

//前序遍历
template <class elemType>
void preorderIteration(binaryTreeNode<elemType> *root)
{
    stack<binaryTreeNode<elemType>*> st;
    if(root)
        st.push(root);

    while(!st.empty()){
        binaryTreeNode<elemType> *cur = st.top();
        st.pop();

        cout << cur->info << " ";//操作当前节点

        if(cur->right)
            st.push(cur->right);
        if(cur->left)
            st.push(cur->left);
    }
}

//中序遍历
template <class elemType>
void inorderIteration(binaryTreeNode<elemType> *root)
{
    stack<binaryTreeNode<elemType>*> st;

    binaryTreeNode<elemType> *cur = root;

    while(cur || !st.empty()){
        if(cur){
            st.push(cur);
            cur = cur->left;
        }
        else{
            cur = st.top();
            st.pop();

            cout << cur->info << " ";//操作当前节点

            cur = cur->right;
        }
    }
}

//后序遍历
template <class elemType>
void postorderIteration(binaryTreeNode<elemType> *root)
{
    stack<binaryTreeNode<elemType>*> st;
    binaryTreeNode<elemType> *pre;

    if(root)
        st.push(root);

    while(!st.empty()){
        binaryTreeNode<elemType> *cur = st.top();
        /*
         * 出栈条件：
         * 对于叶子节点：直接弹出
         * 对于非叶子节点：如果已经遍历过其左子节点或右子节点，则弹出
         */
        if((!cur->left && !cur->right) || (pre && (cur->left == pre || cur->right == pre))){
            st.pop();
            cout << cur->info << " ";//操作当前节点
            pre = cur;
        }
        else{//说明是一个非叶子节点，并且还未访问其左右孩子
            if(cur->right)
                st.push(cur->right);
            if(cur->left)
                st.push(cur->left);
        }
    }
}

template <class elemType>
void BFS(binaryTreeNode<elemType>* btn) {
    if(btn == nullptr)
        return;
	
    queue<binaryTreeNode<elemType> *> que; //构造一个树结点指针的队列
    que.push(btn);
 
    while(!que.empty()){
        binaryTreeNode<elemType> *q = que.front();
        cout << q->info << " ";
        que.pop();
		
        if(q->left != nullptr)  //左子节点入队列
            que.push(q->left);
        if(q->right != nullptr)  //右子节点入队列
            que.push(q->right);
    }
}

int main(){
    binaryTreeNode<int> *a = new binaryTreeNode<int>;
    binaryTreeNode<int> *b = new binaryTreeNode<int>;
    binaryTreeNode<int> *c = new binaryTreeNode<int>;
    binaryTreeNode<int> *d = new binaryTreeNode<int>;
    binaryTreeNode<int> *e = new binaryTreeNode<int>;
    binaryTreeNode<int> *f = new binaryTreeNode<int>;
    binaryTreeNode<int> *g = new binaryTreeNode<int>;

    a->info = 1;
    b->info = 2;
    c->info = 3;
    d->info = 4;
    e->info = 5;
    f->info = 6;
    g->info = 7;

    a->left=b;
    a->right=c;
    b->left=d;
    b->right=e;
    c->left=f;
    c->right=g;

    d->left=nullptr;
    d->right=nullptr;
    e->left=nullptr;
    e->right=nullptr;
    f->left=nullptr;
    f->right=nullptr;
    g->left=nullptr;
    g->right=nullptr;

    BFS(a);
    cout << endl;
    cout << height(a);
    cout << endl;
    preorder(a);
    cout << endl;
    inorder(a);
    cout << endl;
    postorder(a);
    cout << endl;
    preorderIteration(a);
    cout << endl;
    inorderIteration(a);
    cout << endl;
    postorderIteration(a);

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);
    free(g);

    return 0;
}