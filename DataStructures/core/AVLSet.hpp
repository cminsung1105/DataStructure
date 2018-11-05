// AVLSet.hpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include <algorithm>
#include "Set.hpp"
#include <iomanip>
#include <iostream>



template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet() noexcept;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    struct Tree
    {
    	ElementType key;
    	//Tree* parent;
    	Tree* left;
    	Tree* right;
    	int height;
    	Tree(ElementType newKey, Tree* newLeft = nullptr, 
    		Tree* newRight = nullptr, int height = 1);
    };

    Tree* root;
    bool balancing;
    int sz;

private:
	void deleteTree(Tree* tree);
	Tree* copyTree(Tree* tree);
	Tree* addTree(Tree* tree, const ElementType& key);
	int isBalanced(Tree* tree);
	int getHeight(Tree* tree);
	Tree* leftRotation(Tree* tree);
	Tree* rightRotation(Tree* tree);
	void printTree(Tree* tree, int indent = 0);
	bool searchKey(Tree* tree, const ElementType& data) const;
	void preorderTree(Tree* tree, VisitFunction visit) const;
	void inorderTree(Tree* tree, VisitFunction visit) const;
	void postorderTree(Tree* tree, VisitFunction visit) const;



};

template <typename ElementType>
AVLSet<ElementType>::Tree::Tree(ElementType newKey, Tree* newLeft, 
	Tree* newRight, int newHeight)

	:key(newKey), left(newLeft), right(newRight), height(newHeight)
{
}

template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
	: root(nullptr), balancing(shouldBalance), sz(0)
{
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
	deleteTree(root);
	root = nullptr;
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
	root = copyTree(s.root);
	sz =  s.sz;
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
	root = nullptr;
	sz = 0;
	std::swap(root, s.root);
	std::swap(sz, s.sz);
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    Tree* newTree = copyTree(s.root);
    deleteTree(root);
    root = newTree;
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
	std::swap(root, s.root);
	std::swap(sz, s.sz);
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
	root = addTree(root, element);
}


template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
   	return searchKey(root, element);
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return sz;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const
{
	if (root == nullptr)
	{
		return -1;
	}
    else
    {
    	int h = root->height;
    	//std::cout << "HEIGHT FUNCTION: " << h << std::endl;
    	//std::cout << "NEW HEIGHT: " << h-1 << std::endl;
    	return h-1;
    }
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
	preorderTree(root, visit);
}


template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
	inorderTree(root, visit);
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
	postorderTree(root, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::deleteTree(Tree* tree)
{
	if (tree != nullptr)
	{
		if (tree->left != nullptr)
		{
			deleteTree(tree->left);
		}
		if (tree->right != nullptr)
		{
			deleteTree(tree->right);
		}
		delete tree;
	}
	tree = nullptr;
}

template <typename ElementType>
typename AVLSet<ElementType>::Tree* AVLSet<ElementType>::copyTree(Tree* tree)
{
	if (tree == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new Tree(tree->key, copyTree(tree->left), copyTree(tree->right), 
			tree->height);
	}
}


template <typename ElementType>
typename AVLSet<ElementType>::Tree* AVLSet<ElementType>::addTree(
	Tree* tree, const ElementType& key)
{
	//std::cout << "-----NEW ADD TREE-----" << std::endl;
	if (tree == nullptr)
	{
		//add size here
		//std::cout << "ADDED NEW KEY: " <<  key << std::endl;
		++sz;
		return new Tree(key);
	}

	if (key < tree->key)
	{
		//std::cout << "WENT TO THE LEFT" << std::endl;
		tree->left = addTree(tree->left, key);
	}
	else if (key > tree->key)
	{
		//std::cout << "WENT TO THE RIGHT" << std::endl;
		tree->right = addTree(tree->right, key);
	}
	else
	{
		//std::cout << "KEY IS EQUAL" << std::endl;
		return tree;
	}

	int maxHeight;
	maxHeight = std::max(getHeight(tree->left), getHeight(tree->right))+1;
	tree->height = maxHeight;

	//std::cout << "HEIGHT " << tree->key << ": " << tree->height << std::endl;  

	if (balancing)
	{
		int balance;
		balance = isBalanced(tree);

		//std::cout << "BALANCE " << tree->key << ": " << balance << std::endl;

		if (balance > 1)
		{
			if (key < tree->left->key)
			{
				//LL ROTATION
				//std::cout << "LL ROTATION" << std::endl;
				return leftRotation(tree);
			}
			else if (key > tree->left->key)
			{
				//LR ROTATION
				//std::cout << "LR ROTATION" << std::endl;
				tree->left = rightRotation(tree->left);
				return leftRotation(tree);
			}
		}
		else if (balance < -1)
		{
			if (key < tree->right->key)
			{
				//RL ROTATION
				//std::cout << "RL ROTATION" << std::endl;
				tree->right = leftRotation(tree->right);
				return rightRotation(tree);
			}
			else if (key > tree->right->key)
			{
				//RR ROTATION
				//std::cout << "RR ROTATION" << std::endl;
				return rightRotation(tree);
			}
		}
	}
	return tree;
}

template <typename ElementType>
int AVLSet<ElementType>::isBalanced(Tree* tree)
{
	if (tree == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHeight = getHeight(tree->left);
		int rightHeight = getHeight(tree->right);
		//std::cout << "LEFT HEIGHT: " << leftHeight << 
		//	" RIGHT HEIGHT: " << rightHeight << std::endl;
		return leftHeight - rightHeight;
	}
}

template <typename ElementType>
int AVLSet<ElementType>::getHeight(Tree* tree)
{
	if (tree == nullptr)
	{
		return 0;
	}
	else
	{
		return tree->height;
	}
}

template <typename ElementType>
typename AVLSet<ElementType>::Tree* AVLSet<ElementType>::leftRotation(Tree* tree)
{
	Tree* centerTree = tree->left;
	Tree* T3 = centerTree->right;

	centerTree->right = tree;
	tree->left = T3;

	tree->height = std::max(getHeight(tree->left), getHeight(tree->right))+1;
	centerTree->height = std::max(getHeight(centerTree->left), 
		getHeight(centerTree->right))+1;

	//std::cout << "CENTER TREE: " << centerTree->height << std::endl;

	return centerTree;
}

template <typename ElementType>
typename AVLSet<ElementType>::Tree* AVLSet<ElementType>::rightRotation(Tree* tree)
{
	Tree* centerTree = tree->right;
	Tree* T2 = centerTree->left;

	centerTree->left = tree;
	tree->right = T2;

	tree->height = std::max(getHeight(tree->left), getHeight(tree->right))+1;
	centerTree->height = std::max(getHeight(centerTree->left), 
		getHeight(centerTree->right))+1;

	//std::cout << "CENTER TREE: " << centerTree->height << std::endl;

	return centerTree;
}

template <typename ElementType>
void AVLSet<ElementType>::printTree(Tree* tree, int indent)
{
	if (tree != nullptr)
	{
		if (tree->left)
		{
			printTree(tree->left, indent + 4);
		}
		if (tree->right)
		{
			printTree(tree->right, indent + 4);
		}
		if (indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		std::cout << tree->key << std::endl;
	}
}

template <typename ElementType>
bool AVLSet<ElementType>::searchKey(Tree* tree, const ElementType& data) const
{
	if (tree == nullptr)
	{
		return false;
	}
	else if (data < tree->key)
	{
		return searchKey(tree->left, data);
	}
	else if (data > tree->key)
	{
		return searchKey(tree->right, data);
	}
	else if (data == tree->key) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename ElementType>
void AVLSet<ElementType>::preorderTree(Tree* tree, VisitFunction visit) const
{
	if (tree == nullptr)
	{
		return;
	}
	visit(tree->key);
	preorderTree(tree->left, visit);
	preorderTree(tree->right, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::inorderTree(Tree* tree, VisitFunction visit) const
{
	if (tree == nullptr)
	{
		return;
	}
	inorderTree(tree->left, visit);
	visit(tree->key);
	inorderTree(tree->right, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::postorderTree(Tree* tree, VisitFunction visit) const
{
	if (tree == nullptr)
	{
		return;
	}
	postorderTree(tree->left, visit);
	postorderTree(tree->right, visit);
	visit(tree->key);
}

#endif // AVLSET_HPP

