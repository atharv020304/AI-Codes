#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
#include<algorithm>


using namespace std;


class node{
    public:
    int data;
    node* left;
    node* right;
};




void bfs(node* root){
    if(root == NULL){
        return;
    }
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if(temp->left != NULL){
            q.push(temp->left);
        }
        if(temp->right != NULL){
            q.push(temp->right);
        }
    }
}


void bfs2(node* root){
    if(root == NULL){
        return;
    }
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if(temp->right != NULL){
            q.push(temp->right);
        }
        if(temp->left != NULL){
            q.push(temp->left);
        }
       
    }
}


void dfs(node* root){
    if(root == NULL){
        return;
    }
    stack<node*> s;
    s.push(root);
    while(!s.empty()){
        node* temp = s.top();
        s.pop();
        cout << temp->data << " ";
        if(temp->right != NULL){
            s.push(temp->right);
        }
        if(temp->left != NULL){
            s.push(temp->left);
        }
    }
}


void dfs2(node* root){
    if(root == NULL){
        return;
    }
    stack<node*> s;
    s.push(root);
    while(!s.empty()){
        node* temp = s.top();
        s.pop();
        cout << temp->data << " ";
        if(temp->left != NULL){
            s.push(temp->left);
        }
        if(temp->right != NULL){
            s.push(temp->right);
        }
       
    }
}



int main(){
    node* root = new node();
    root->data = 1;
    root->left = new node();
    root->left->data = 2;
    root->left->left = new node();
    root->left->left->data = 3;
    root->left->right = new node();
    root->left->right->data = 4;
    root->right = new node();
    root->right->data = 5;
    root->right->left = new node();
    root->right->left->data = 6;
    root->right->right = new node();
    root->right->right->data = 7;


    bfs2(root);
    cout << endl;
    bfs(root);
    cout << endl;
    dfs(root);
    cout << endl;
    dfs2(root);
}
