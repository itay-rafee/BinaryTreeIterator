#pragma once
#include<iostream>
#include <queue>
#include<array>


using namespace std;
namespace ariel
{
    template <typename T>
    class BinaryTree
    {
        /* Node struct */
        struct Node
        {
            T data;
            Node* parent;
            Node* left;
            Node* right;

            Node(T d, Node* p=nullptr):data(d), left(nullptr), right(nullptr), parent(p){}
        };

    private:
        Node* root;

        /* help method for: add_left, add_right */
        Node& find_node(T d){
            queue<Node*> q;
            q.push(root);
            Node* n = nullptr;
            while (!q.empty())
            {
                n = q.front();
                q.pop();
                if (n != nullptr){
                    if (n->data == d){break;}
                    q.push(n->left);
                    q.push(n->right);
                }
            }
            return *n;
        }

    public:
        BinaryTree():root(nullptr){}
        // ~BinaryTree(){delete_tree(root);}
        // void delete_tree(Node* n){
        //     if (n->left != nullptr){delete_tree(n->left);}
        //     if (n->right != nullptr){delete_tree(n->right);}
        //     delete[] n;
        // }

        /* add root for the tree */
        BinaryTree<T> add_root(T r){
            if (root == nullptr){root = new Node(r);}
            else{root->data = r;}
            return *this;
        }

        /* add left child for the patent */
        BinaryTree<T> add_left(T parent, T child){
            if (root == nullptr){throw invalid_argument("there is no root");}

            Node* n = &find_node(parent);
            if (n == nullptr){throw invalid_argument("there is no parent");}

            if (n->left == nullptr){n->left = new Node(child);}
            else{n->left->data = child;}

            return *this;
        }

        /* add right child for the patent */
        BinaryTree<T> add_right(T parent, T child){
            if (root == nullptr){throw invalid_argument("there is no root");}

            Node* n = &find_node(parent);
            if (n == nullptr){throw invalid_argument("there is no parent");}

            if (n->right == nullptr){n->right = new Node(child);}
            else{n->right->data = child;}

            return *this;
        }

        /* =============================== */
        /*     preorder iterator class     */
        /* =============================== */
        class iterator_preorder
        {
        private:
            Node* node;
            vector<Node*> vec;
            size_t count = 0;

        public:
            iterator_preorder(Node* n){
                set_vec(n);
                vec.push_back(nullptr);
            }

            void set_vec(Node* n){
                if (n != nullptr)
                {
                    vec.push_back(n);
                    set_vec(n->left);
                    set_vec(n->right);
                }
            }

            T &operator*() const {
                return vec.at(count)->data;
            }
            T *operator->() const {
                return vec.at(count).data;
            }

            // ++i;
            iterator_preorder &operator++(){
                ++count;
                return *this;
            }
            // i++;
            const iterator_preorder operator++(int){
                iterator_preorder it = *this;
                count++;
                return it;
            }
            bool operator==(const iterator_preorder &rhs) const {
                return vec.at(count) == rhs.vec.at(rhs.count);
            }
            bool operator!=(const iterator_preorder &rhs) const {
                return vec.at(count) != rhs.vec.at(rhs.count);
            }

        };


        /* =============================== */
        /*      inorder iterator class     */
        /* =============================== */
        class iterator_inorder
        {

        private:
            Node* node;
            vector<Node*> vec;
            size_t count = 0;

        public:
            iterator_inorder(Node* n){
                set_vec(n);
                vec.push_back(nullptr);
            }

            void set_vec(Node* n){
                if (n != nullptr)
                {
                    set_vec(n->left);
                    vec.push_back(n);
                    set_vec(n->right);
                }
            }

            T &operator*() const {
                return vec.at(count)->data;
            }
            T *operator->() const {
                return vec.at(count)->data;
            }

            // ++i;
            iterator_inorder &operator++(){
                ++count;
                return *this;
            }
            // i++;
            const iterator_inorder operator++(int){
                iterator_inorder it = *this;
                count++;
                return it;
            }
            bool operator==(const iterator_inorder &rhs) const {
                return vec.at(count) == rhs.vec.at(rhs.count);
            }
            bool operator!=(const iterator_inorder &rhs) const {
                return vec.at(count) != rhs.vec.at(rhs.count);
            }

        };


        /* =============================== */
        /*     postorder iterator class    */
        /* =============================== */
        class iterator_postorder
        {
        private:
            Node* node;
            vector<Node*> vec;
            size_t count = 0;

        public:
            iterator_postorder(Node* n){
                set_vec(n);
                vec.push_back(nullptr);
            }
            // ~iterator_postorder(){delete[] vec;}

            void set_vec(Node* n){
                if (n != nullptr)
                {
                    set_vec(n->left);
                    set_vec(n->right);
                    vec.push_back(n);
                }
            }

            T &operator*() const {
                return vec.at(count)->data;
            }
            T *operator->() const {
                return &vec.at(count)->data;
            }

            // ++i;
            iterator_postorder &operator++(){
                ++count;
                return *this;
            }
            // i++;
            const iterator_postorder operator++(int){
                iterator_postorder it = *this;
                count++;
                return it;
            }
            bool operator==(const iterator_postorder &rhs) const {
                return vec.at(count) == rhs.vec.at(rhs.count);
            }
            bool operator!=(const iterator_postorder &rhs) const {
                return vec.at(count) == rhs.vec.at(rhs.count);
            }
        };


        /* begin & end preorder */
        iterator_preorder begin_preorder(){
            return iterator_preorder{root};
        }
        iterator_preorder end_preorder(){
            return iterator_preorder{nullptr};
        }

        /* begin & end inorder */
        iterator_inorder begin_inorder(){
            Node* n  = root;
            while (n->left != nullptr)
            {
                n = n->left;
            }
            return iterator_inorder{n};
        }
        iterator_inorder end_inorder(){
            return iterator_inorder{nullptr};
        }

        /* begin & end postorder */
        iterator_postorder begin_postorder(){
            Node* n  = root;
            while (n->left != nullptr)
            {
                n = n->left;
            }
            return iterator_postorder{n};
        }
        iterator_postorder end_postorder(){
            return iterator_postorder{nullptr};
        }

        /* General begin & end */
        iterator_inorder begin(){return this->begin_inorder();}
        iterator_inorder end(){return this->end_inorder();}

        friend std::ostream &operator<<(std::ostream &out, BinaryTree<T> &t) {
            return out;
        }

    };

}