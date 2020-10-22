#include "BinarySearchTree.h"

TreeNode::TreeNode(int count, Tile* tile, TreeNode* parent, TreeNode* left, TreeNode* right) :
    count(count),
    tile(tile),
    parent(parent),
    left(left),
    right(right)
{
}
TreeNode::TreeNode(TreeNode& other)
    : count(other.count), tile(other.tile), parent(other.parent), left(nullptr), right(nullptr) {
    if (other.left != nullptr) {
        left = new TreeNode(*other.left);    // recursively call copy constructor
    }  
    if (other.right != nullptr) {
        right = new TreeNode(*other.right);  // recursively call copy constructor
    }
    
}

TreeNode::~TreeNode() {

}

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    delete root;
    root = nullptr;
}

TreeNode* BinarySearchTree::getRoot() {
    return root;
}

void BinarySearchTree::insert(Tile* tile) {

    root = insert(root, tile);
}

TreeNode* BinarySearchTree::insert(TreeNode* node, Tile* tile) {

    // if given node is null
    if (node == NULL) {
        // initialise node as a new node with given tile
        node = new TreeNode(1, tile, nullptr, nullptr, nullptr);

    // else if the given tile has the same colour as the given node's tile's colour
    } else if (tile->getColour() == node->tile->getColour()) {
        // increment the node's count
        ++node->count;

    // else if the tile's colour is greater    
    } else if (tile->getColour() > node->tile->getColour()) {
        // recursively call insert function with the node's right child
        node->right = insert(node->right, tile);
        // the right child's parent becomes the node
        node->right->parent = node;
    } else {

        // recursively call insert function with the node's left child
        node->left = insert(node->left, tile);
        // left child's parent becomes the node
        node->left->parent = node;
    }

    return node;
}

void BinarySearchTree::printTreeInOrder() {
    printTreeInOrder(root);
    std::cout << std::endl;
}

void BinarySearchTree::printTreeInOrder(TreeNode* node) {
    // if the node is nullptr
    if (node == nullptr) {
        // do nothing
    // else
    } else {
        // recursively call print function with the left child
        printTreeInOrder(node->left);

        // iteratively print the current node's tile's colour equal to the value of its count
        for (int i = 1; i <= node->count; ++i) {
            node->tile->printLetter();
        }
        // recursively call print function with the right child
        printTreeInOrder(node->right);
    }
}

bool BinarySearchTree::search(Tile* tile) {

    TreeNode* node = search(root, tile);
    
    bool found = false;
    if (node != nullptr) {
        found = true;
    }
    return found;
}

TreeNode* BinarySearchTree::search(TreeNode* node, Tile* tile) {
    // if node is not nullptr
    if (node != nullptr) {
        // if the node's tile's colour is equal to the tile's colour
        if (node->tile->getColour() == tile->getColour()) {
            // do nothing
        // else if the node's tile's colour is lesser
        } else if (node->tile->getColour() < tile->getColour()) {
            // recursively call the search function with the node's right child
            node = search(node->right, tile);
            // else if the node's tile's colour is greater
        } else if (node->tile->getColour() > tile->getColour()) { 
            // recursively call the search function with the node's left child
            node = search(node->left, tile);
        }
    }

    return node;
}

int BinarySearchTree::findMin() {
    return findMin(root);
}

int BinarySearchTree::findMin(TreeNode* node) {
    int min = 7;
    if (node == nullptr) {
        min = -1;
    // else if node's left child is nullptr, i.e. there is no node with smaller value
    } else if (node->left == nullptr) {
        // set min with the node's value
        min = node->tile->getColour();
    } else {
        // else recursively call the findMin function with the left child
        findMin(node->left);
    }
    return min;
}

int BinarySearchTree::findMax() {
    return findMax(root);
}

int BinarySearchTree::findMax(TreeNode* node) {
    int max = 0;
    if (node == nullptr) {
        max = -1;
    // else if node's rightt child is nullptr, i.e. there is no node with larger value
    } else if (node->right == nullptr) {
        // set max with the node's value
        max = node->tile->getColour();
    } else {
        // else recursively call the findMin function with the right child
        findMin(node->right);
    }

    return max;
}

int BinarySearchTree::successor(Tile* tile) {

    int value = 0;

    TreeNode* node = search(root, tile);

    if (node == nullptr) {
        value = -1;
    } else {
        value = successor(node);
    }

    return value;
}

int BinarySearchTree::successor(TreeNode* node) {
    
    int value = 0;
    // if right child is not nullptr
    if (node->right != nullptr) {
        // value is set to the min of the right child
        value = findMin(node->right);
    } else {
        // initialise node_parent as the current node's parent and node_current as the current node
        TreeNode* node_parent = node->parent;
        TreeNode* node_current = node;

        // while node_parent is not nullptr and node_current is equal to the parent's right child
        while (node_parent != nullptr && node_current == node_parent->right) {
            // node_current is set as node_parent
            node_current = node_parent;
            // node_parent is set as node_current's parent
            node_parent = node_current->parent;
        }
    }
    return value;
}

int BinarySearchTree::predecessor(Tile* tile) {

    int value = 7;

    TreeNode* node = search(root, tile);

    if (node == nullptr) {
        value = -1;
    } else {
        value = successor(node);
    }

    return value;
}

int BinarySearchTree::predecessor(TreeNode* node) {

    int value = 0;
    // if left child is not nullptr
    if (node->left != NULL) {
        // value is set to the min of the left child
        return findMax(node->left);
    } else {
        // initialise node_parent as the current node's parent and node_current as the current node
        TreeNode* node_parent = node->parent;
        TreeNode* node_current = node;

        // while node_parent is not nullptr and node_current is equal to the parent's leftt child
        while (node_parent != nullptr && node_current == node_parent->left) {
            // node_current is set as node_parent
            node_current = node_parent;
            // node_parent is set as node_current's parent
            node_parent = node_current->parent;
        }
    }

    return value;
}

void BinarySearchTree::remove(Tile* tile) {
    root = remove(root, tile);
}

TreeNode* BinarySearchTree::remove(TreeNode* node, Tile* tile) {
    // if node is not nullptr
    if (node != nullptr) {
        // if the node's tile's colour is equal to the given tile's colour
        if (node->tile->getColour() == tile->getColour()) {
            // if both childs of the node are nullptr
            if (node->left == nullptr && node->right == nullptr) {
                // if the count of the node is greater than 1
                if (node->count > 1) {
                    // decrement the count
                    --node->count;
                } else {
                    // else delete the node and set it to nullptr
                    delete node;
                    node = nullptr;
                }
            // else if only the left child is nullptr
            } else if (node->left == nullptr && node->right != nullptr) {
                // set the right child's parent as the current node's parent
                // set the current node as the right node
                node->right->parent = node->parent;
                node = node->right;
            // else if only the rightt child is nullptr
            } else if (node->left != nullptr && node->right == nullptr) {
                // set the left child's parent as the current node's parent
                // set the current node as the left node
                node->left->parent = node->parent;
                node = node->left;
            } else {
                // else initialise value as the successor of the given tile
                int value = successor(tile);
                // current node's tile is initialised as a new tile with colour as the value cast to Colour enum
                node->tile = new Tile((Colour) value);
                // recursively call the remove function with the right child and the new tile with colour  as the value cast to Colour enum
                node->right = remove(node->right, new Tile((Colour) value));
            }
        // else if the node's tile's value is less than the tile's value
        } else if (node->tile->getColour() < tile->getColour()) {
            // if the right child is not nullptr
            if (node->right != nullptr) {
                // recursively call the remove function with the right child and the given tile
                node->right = remove(node->right, tile);
            }
        } else {
            // else, if the left child is nullptr
            if (node->left != nullptr) {
                // recursively call the remove function with the left child and the given tile
                node->left = remove(node->left, tile);
            }
        }
    }
    return node;
}

TreeNode* BinarySearchTree::visitLeaf(TreeNode* node) {
    // if the left child is not nullptr
    if(node->left != nullptr) {
        // recursively call visitLeaf with the left child
        visitLeaf(node->left);
    // else if both childs are nullptr
    } else if (node->left == nullptr && node->right == nullptr) {
        // do nothing
    }
    // if the right child is not nullptr
    if(node->right != nullptr) {
        // recursively call visitLeaf with the right child
        visitLeaf(node->right);
    // else if both childs are nullptr
    } else if (node->left == nullptr && node->right == nullptr) {
        // do nothing
    }

    return node;
}
