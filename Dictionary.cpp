#include "Dictionary.h"
#include<iostream>
#include<string>
#include <string>      
#include <sstream>

#define RED 0
#define BLACK 1
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

bool Dictionary::is_null(Node* R) const{
    return (R == nil);
}


Dictionary::Node* Dictionary::contains_node(keyType k) const{
    Node* curr = root;
    if(is_null(curr)){
        return nil;
    }

    while (true){

        if(k.compare(curr->key) < 0){
            if(is_null(curr->left)){
                return nil;
            }
            curr = curr->left;
        }else if (k.compare(curr->key) > 0){
            if(is_null(curr->right)){
                return nil;
            }
            curr = curr->right;
        }else{
            return curr;
        }
        
    }
    return nil;
}

Dictionary::Node* Dictionary::findMin(Node* R){
    Node* c = R;
    while((!is_null(c->left))){
        c = c->left;
    }
    return c;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    Node* c = R;
    while(!(is_null(c->right))){
        c = c->right;
    }
    return c;
}

void Dictionary::LeftRotate(Node* x){

    Node* y = x->right;

    x->right = y->left;

    //Maybe not necessary
    if(is_null(y->left) == false){
        y->left->parent = x;
    }

    y->parent = x->parent;
    if(is_null(x->parent)){
        root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void Dictionary::RightRotate(Node* x){
    Node* y = x->left;
    
    x->left = y->right;

    y->right->parent = x;

    y->parent = x->parent;
    if(is_null(x->parent)){
        root = y;
    }else if(x == x->parent->right){
        x->parent->right = y;
    }else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}



void Dictionary::RB_Transplant(Node* u, Node* v){
    if(is_null(u->parent)){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent = u->parent;

}

void Dictionary::RB_Delete(Node* z){
    Node* y = z;
    Node* x;
    int y_original_color = y->color;
    if(is_null(z->left)){
        x = z->right;
        RB_Transplant(z, z->right);
    }else if(is_null(z->right)){
        x = z->left;
        RB_Transplant(z, z->left);
    }
    else{
        y = findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }else{
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(z == current){
        current = nil;
    }
    delete(z);
    num_pairs--;
    if(y_original_color == BLACK){
        RB_DeleteFixUp(x);
    }
}

void Dictionary::RB_DeleteFixUp(Node* x){
    Node* w;
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if((w->left->color == BLACK) && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
                if (w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        }
        else{
            w = x->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if((w->right->color == BLACK) && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
                if (w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }


    }
    x->color = BLACK;
}

Dictionary::Dictionary(){
    Node *n = new Node("", -1);
    //n->parent = n;
    //n->left = n;
    //n->right = n;
    //n->color = RED;
    
    nil = n;
    root = nil;
    current = nil;
    

    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
   
    nil = new Node("", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
    
}

Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete(nil);
}


void Dictionary::postOrderDelete(struct Node* R){
    if(is_null(R)){
        return;
    }

    
    if((!is_null(R->left))){

        postOrderDelete(R->left);
    }

    if((!is_null(R->right))){

        postOrderDelete(R->right);
    }


    if(is_null(R->parent)){
        root = nil;
    }else if (R->key.compare(R->parent->left->key) == 0){
        R->parent->left = nil;
    }else{
        R->parent->right = nil;
    }
    num_pairs--;
    delete(R);
    return;
}

//Access Functions
int Dictionary::size() const{
    return num_pairs;
}

keyType* contains_call_keytype;
valType* contains_call_valtype;
bool Dictionary::contains(keyType k) const{
    Node* curr = root;

    while (curr != nullptr){

        if(k.compare(curr->key) == 0){
            contains_call_valtype = &curr->val;
            contains_call_keytype = &curr->key;
            return true;
        }else if(k.compare(curr->key) < 0){
            curr = curr->left;
        }else{
            curr = curr->right;
        }
    }
    return false;
}

valType& Dictionary::getValue(keyType k) const{
    if(contains(k)){
        return *contains_call_valtype;
    }
    throw std::invalid_argument("Dictionary: getValue(): given key doesn't exist\n");
}

bool Dictionary::hasCurrent() const{
    if(is_null(current)){
        //printf("false\n");
        return false;
    }
    return true;
}

keyType Dictionary::currentKey() const{
    if(hasCurrent()){
        return current->key;
    }
    else{
        throw std::invalid_argument("Dictionary: currentKey(): current does not exist\n");
    }
}

valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        return current->val;
    }
    else{
        throw std::invalid_argument("Dictionary: currentVal(): current does not exist\n");
    }
}

void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
}
void Dictionary::RB_InsertFixUp(Node* z){
    Node* y;
    while (is_null(z->parent) == false && z->parent->color == RED){
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if (y->color == RED){
                //std::cout << "case 1\n";
                z->parent->color = BLACK;          // case 1
                y->color = BLACK;                     // case 1
                z->parent->parent->color = RED;         // case 1
                z = z->parent->parent;                 // case 1
            }else{     
                if (z == z->parent->right){
                    //std::cout << "case 2\n";
                    z = z->parent;                     // case 2
                    LeftRotate(z);                 // case 2
                }
                //std::cout << "case 3\n";
                z->parent->color = BLACK;              // case 3
                z->parent->parent->color = RED;         // case 3
                //std::cout << "right top\n";
                RightRotate(z->parent->parent);     // case 3
            }
        }     
        else {
            y = z->parent->parent->left;
            if (y->color == RED){
                //std::cout << "case 4\n";
                z->parent->color = BLACK;              // case 4
                y->color = BLACK;                     // case 4
                z->parent->parent->color = RED;         // case 4
                z = z->parent->parent;                 // case 4
            }else{

                if (z == z->parent->left){
                    //std::cout << "case 5\n";
                    z = z->parent;                     // case 5
                    //std::cout << "right bot\n";
                    RightRotate(z);                // case 5
                }
                //std::cout << "case 6\n";
                z->parent->color = BLACK;              // case 6
                z->parent->parent->color = RED;         // case 6
                //std::cout << "Left bot\n";
                //std::cout << "Was\n";
                //std::cout << pre_string();
                LeftRotate(z->parent->parent);      // case 6
                //std::cout << "Now\n";
                //std::cout << pre_string();
            }
        } 
    }
    root->color = BLACK;
}
void Dictionary::RB_Insert(Node* z){
    Node* y = nil;
    Node* x = root;
    while (is_null(x) == false){
        y = x;
        int com = z->key.compare(x->key);
        if (com < 0){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(is_null(y)){
        //std::cout << "setting root\n";
        root = z;
    }else if( z->key.compare(y->key) < 0){
        y->left = z;
    }else{
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = RED;
    RB_InsertFixUp(z);
}

void Dictionary::setValue(keyType k, valType v){
    Node* n = contains_node(k);
    //std::cout <<"found node\n";
    if(is_null(n) == false){
        n->val = v;
    }else{
        //std::cout << "Adding " + k + "\n";
        Node* z = new Node(k, v);
        //std::cout << "inserting:" + k + "\n";
        num_pairs++;
        RB_Insert(z);
        //std::cout << "color: " + std::to_string(z->color) + "\n";
    }

}
void Dictionary::transplant(Node* u, Node* v){
    Node* par = u->parent;
    if(is_null(par)){
        root = v;
    }else if (u == par->left){
        par->left = v;
    }else{
        par->right = v;
    }

    if (is_null(v) == false){
        v->parent = par;
    }
}
void Dictionary::remove(keyType k){
   
   Node* z = contains_node(k);

   if(is_null(z)){
        throw std::logic_error("Dictionary: remove(): Key does not exist\n");
    }


   RB_Delete(z);
}

void Dictionary::begin(){
    if(num_pairs == 0){
        return;
    }
    Node* c = root;
    while (c->left != nil){
        c = c->left;
    }
    current = c;
}

void Dictionary::end(){
    if(num_pairs == 0){
        return;
    }
    Node* c = root;
    while (c->right != nil){
        c = c->right;
    }
    current = c;
}

void Dictionary::next(){
    Node* c = current;
    if(current == nil){
        throw std::range_error("Dictionary: Next(): No current node, cant find next\n");
    }

    if(is_null(current->right) == false){
        current = findMin(current->right);
        return;
    }
    c = c->parent;
    
    while(c->key.compare(current->key) <= 0){
        c = c->parent;

        if(is_null(c)){
            current = nil;
            return;
        }
    }
    current = c;
    return;
}

void Dictionary::prev(){
    Node* c = current;
    if(current == nil){
        throw std::range_error("Dictionary: prev(): No current node, cant find next\n");
    }

    if(is_null(current->left) == false){
        current = current->left;
        return;
    }
    c = c->parent;
    while(c->key.compare(current->key) >= 0){
        c = c->parent;
        if(is_null(c)){
            current = nil;
            return;
        }
    }
    current = c;
    return;
}

std::string col = " : ";
std::string newL = "\n";
                                                        //const
void Dictionary::inOrderString(std::ostream& output,Node* R) const{
    if(is_null(R)){
        return;
    }

    if(is_null(R->left) == false){
        inOrderString(output, R->left);
    }

    output << (R->key + col + std::to_string(R->val) + newL);

    if(is_null(R->right) == false){
        inOrderString(output, R->right);
    }

    return;
}

void Dictionary::preOrderString(std::ostream& output, Node* R) const{
    if(is_null(R)){
        return;
    }
    output << (R->key+ newL);
    
    if(is_null(R->left) == false){
        preOrderString(output, R->left);
    }

    if(is_null(R->right) == false){
        preOrderString(output, R->right);
    }

}

std::string Dictionary::to_string() const{
    std::stringstream s;
    Node* r = root;
    inOrderString(s, r);
    return s.str();

}

std::string Dictionary::pre_string() const{
    std::stringstream s;
    Node* r = root;
    preOrderString(s, r);
    return s.str();
}


bool Dictionary::equals(const Dictionary& D) const{
    std::string A = to_string();
    std::string B = D.to_string();

    if(A.compare(B) == 0){
        return true;
    }
    return false;
}


void Dictionary::preOrderCopy(Node*R, Node* N){

    if(R->key.compare(N->key) == 0){
        return;
    }

    setValue(R->key, R->val);

    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D){
    D.inOrderString(stream, D.root);
    return stream;
}

bool operator==( const Dictionary& A, const Dictionary& B){
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){

    clear();
    preOrderCopy(D.root, nil);

    return *this;
}
