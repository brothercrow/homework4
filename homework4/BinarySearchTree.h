
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    //*********** ADD A POINTER TO FUNCTION MEMBER VARIABLE AS DESCRIBED ON THE ASSIGNMENT********
    //template <class ItemType>
    int(*compareCards)(const ItemType&, const ItemType&);
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

public:
    //*********** ADD A CONSTRUCTOR AS DESCRIBED ON THE ASSIGNMENT********
    BinarySearchTree<ItemType>(int compare(const Itemtype&, const ItemType&){ compareCards = compare; };
    //*********** ADD A COPY CONSTRUCTOR AS DESCRIBED ON THE ASSIGNMENT********
    BinarySearchTree<ItemType>(BinaryTree<ItemType>* sourceTree){ rootPtr = copyTree(sourceTree.rootPtr); };
    // insert a node at the correct location
    bool insert(const ItemType & newEntry);
    // remove a node if found
    bool remove(const ItemType & anEntry);
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    // NOT IN THE Tree Code Files on Catalyst, use for HW#4:
    BinarySearchTree & operator=(const BinarySearchTree & sourceTree);
    // YOU WRITE: gets the "smallest" Item
    void getFirst(ItemType &firstItem);
    // YOU WRITE: returns the "largest" Item
    void getLast(ItemType &lastItem);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    rootPtr = _insert(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    rootPtr = _remove(rootPtr, target, isSuccessful);
    return isSuccessful;
}

//*****************************COMPLETE THIS******************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    // MUST INCLUDE CALLING THE PRIVATE findNode FUNCTION
    // Be sure to check if the findNode function actually finds anEntry
    // If it does, assign to the returnedItem parameter the item of the 
    //     found node and return true
    // If it doesn't, return false
    returnedItem = findNode(anEntry);
    if (returnedItem != 0)
	   return true;
    else
	   return false;
}

//NOT IN THE Tree Code Files on Catalyst, use for HW#4:
template<class ItemType>
BinarySearchTree<ItemType> & BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType> & sourceTree)
{
    compare = sourceTree.compare;
    this->BinaryTree::operator=(sourceTree);
    return *this;
}

template<class ItemType>
void BinarySearchTree<ItemType>::getFirst(ItemType &firstItem)
{
    // NON-recursive algorithm:
    // If the tree is empty, just return
    // FIND THE LEFT-MOST LEFT CHILD
    // WHEN you can't go left anymore, assign the node's data to firstItem
    if (rootPtr == 0)
	   return;
   BinaryNode<ItemType>* current = rootPtr;
    while (!current->isLeaf())
    {
		  current = current->getLeftPtr();
    }
    firstItem = current->getItem();
    return; 
}

template<class ItemType>
void BinarySearchTree<ItemType>::getLast(ItemType &lastItem)
{
    // If the tree is empty, just return
    // FIND THE RIGHT-MOST RIGHT CHILD
    // WHEN you can't go RIGHT anymore, assign the node's data to lastItem
    if (rootPtr == 0)
	   return;
    BinaryNode<ItemType>* current = rootPtr;
    while (!current->isLeaf())
    {
	   current = current->getRightPtr();
    }
    firstItem = current->getItem();
    return;
}
//////////////////////////// private functions //////////////////////////////////

// Done as class exercise:
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
    BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == 0)
	   return newNodePtr;
    if (newNodePtr->getItem() < nodePtr->getItem()) //*****CHANGE THIS*****
	   nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    else
	   nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
    return nodePtr; // must return
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
    const ItemType target, bool & success)
{
    if (nodePtr == 0)
    {
	   success = false;
	   return 0;
    }
    if (nodePtr->getItem() > target) //*****CHANGE THIS*****
	   nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem() < target) //*****CHANGE THIS*****
	   nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else	// found the node
    {
	   nodePtr = deleteNode(nodePtr);
	   success = true;
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
	   delete nodePtr;
	   nodePtr = 0;
	   return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
	   BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
	   delete nodePtr;
	   nodePtr = 0;
	   return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
	   BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
	   delete nodePtr;
	   nodePtr = 0;
	   return nodeToConnectPtr;
    }
    else
    {
	   ItemType newNodeValue;
	   nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
	   nodePtr->setItem(newNodeValue);
	   return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
    ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
	   successor = nodePtr->getItem();
	   return deleteNode(nodePtr);
    }
    else
    {
	   nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
	   return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
    const ItemType & target) const
{
    // ALGORITHM:
    //       IF nodePtr doesn't exist (is 0) THEN
    //            return 0
    if (nodePtr == 0)
	   return 0;
    else if (compareCards(nodePtr->getItem(), target) > 0)
	  return findNode(nodePtr->getLeftPtr(), target);
	   //       ELSE IF nodePtr's item > target THEN (make sure you use the compare function)
	   //                return what the recursive call to findNode, for the leftPtr, returns
    else if (compareCards(nodePtr->getItem(), target) < 0)
	  return findNode(nodePtr->getRightPtr(), target);
    //       ELSE IF nodePtr's item < target THEN (make sure you use the compare function)
    //            return what the recursive call to findNode, for the rightPtr, returns
    //	ELSE
    return nodePtr;

}
