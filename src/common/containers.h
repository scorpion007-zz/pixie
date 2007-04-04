//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
//
//	This library is free software; you can redistribute it and/or
//	modify it under the terms of the GNU Lesser General Public
//	License as published by the Free Software Foundation; either
//	version 2.1 of the License, or (at your option) any later version.
//
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//	Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public
//	License along with this library; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//  File				:	containers.h
//  Classes				:	CDictionary
//							CHash
//							CTrie
//							CPqueue
//							CMemPool
//							CMemStack
//							CArray
//  Description			:	Misc template data structures
//
////////////////////////////////////////////////////////////////////////
#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stdio.h>
#include <string.h>

#include "global.h"
#include "align.h"










///////////////////////////////////////////////////////////////////////
// Class				:	CDictionary
// Description			:	Pure virtual parent class for dictionary
// Comments				:
template <class keyType,class valType> class CDictionary  {
public:
						CDictionary()	{	}
	virtual				~CDictionary()	{	}

						// inserts an entity into the dictionary
	virtual	void		insert(keyType,valType)				=	0;
						// return 1 if the entity is found in the dictionary
	virtual	int			find(keyType,valType &)	const		=	0;
						// return 1 if the entity is found in the dictionary and erase it
	virtual	int			erase(keyType,valType &)			=	0;
						// Delete the dictionary including everything in it
	virtual	void		destroy()							=	0;
};










///////////////////////////////////////////////////////////////////////
// Class				:	CHash
// Description			:	Hash table
// Comments				:
template <class keyType,class valType>	class CHash : public CDictionary<keyType,valType> {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CHashBucket
	// Description			:	Hash table
	// Comments				:
	class CHashBucket {
	public:
		keyType		key;
		valType		val;
		CHashBucket	*next;
	};

public:
						// Constructor
						CHash(int nb = 7) {
							int			i;
							nBuckets	=	1 << nb;
							buckets		=	new CHashBucket*[nBuckets];
							for (i=0;i<nBuckets;i++)
								buckets[i]	=	NULL;
						}

						// Destructor
						~CHash() {
							CHashBucket	*h;
							int			i;

							for (i=0;i<nBuckets;i++) {
								for (h=buckets[i];h!=NULL;h=buckets[i]) {
									buckets[i]	=	buckets[i]->next;
									delete h;
								}
							}

							delete [] buckets;
						}

				
						// Insert another item into the hash
	void				insert(keyType k,valType v)	{
							int				index	=	key(k);
							CHashBucket		*h		=	new CHashBucket;

							h->key			=	k;
							h->val			=	v;
							h->next			=	buckets[index];
							buckets[index]	=	h;
						}

						// Find an item in the hash
	int					find(keyType k,valType &v) const {
							int				index	=	key(k);
							CHashBucket		*h;

							for(h=buckets[index];h!=NULL;h=h->next) {
								if (keycmp(h->key,k)) {
									v	=	h->val;
									return TRUE;
								}
							}

							return FALSE;
						}

						// Find/erase an item from the hash
	int					erase(keyType k,valType &v) {
							int				index	=	key(k);
							CHashBucket		*h;
							CHashBucket		*h1;

							for(h1=NULL,h=buckets[index];h!=NULL;h1=h,h=h->next) {
								if (keycmp(h->key,k)) {
									v	=	h->val;

									if (h1 == NULL) buckets[index]	=	h->next;
									else			h1->next		=	h->next;
										
									delete h;

									return TRUE;
								}
							}

							return FALSE;
						}


						// Delete the hash with everything in it
	void				destroy() {
							CHashBucket	*h;
							int			i;

							for (i=0;i<nBuckets;i++) {
								h			=	buckets[i];

								for(h=buckets[i];h!=NULL;h=buckets[i]) {
									buckets[i]	=	buckets[i]->next;
									delete h->val;
									delete h;
								}

								buckets[i]	=	NULL;
							}

							delete this;
						}

	int					nBuckets;		// The number of buckets
	CHashBucket			**buckets;		// The array of buckets
private:
	int					key(const char *s) const {
							int	index	=	0;

							for (;*s != '\0';s++)
								index	+=	(*s)*(*s);

							return index & (nBuckets-1);
						}

	int					key(int s) const {
							return ((s*s) + s) & (nBuckets-1);
						}

	int					keycmp(const char *s1,const char *s2) const {
							if (strcmp(s1,s2) == 0) return TRUE;
							return FALSE;
						}

	int					keycmp(int s1,int s2) const {
							if (s1 == s2) return TRUE;
							return FALSE;
						}
};

















// Some misc macros
#define	isLeaf(__node)		(((uintptr_t) __node) & 1)
#define	getLeaf(__node)		(CTrieLeaf *) (((uintptr_t) __node) & (~1))
#define	makeNode(__node)	(CTrieNode *) (((uintptr_t) __node) | 1)

///////////////////////////////////////////////////////////////////////
// Class				:	CTrie
// Description			:	Trie class
// Comments				:
template <class valType> class CTrie : public CDictionary<const char *,valType> {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CTrieLeaf
	// Description			:	Encapsulates a trie leaf
	// Comments				:
	class CTrieLeaf {
	public:
		CTrieLeaf(const char *k,valType v) {
			key		=	k;
			val		=	v;
		}

		valType		val;
		const  char	*key;
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CTrieNode
	// Description			:	Encapsulates a trie internal node
	// Comments				:
	class CTrieNode {
	public:
		CTrieNode() {
			int i;

			for (i=0;i<256;i++) pointers[i]	=	NULL;
		}

		~CTrieNode() {
			int i;

			for (i=0;i<256;i++) {
				if (pointers[i] != NULL) {
					if (isLeaf(pointers[i]))
						delete getLeaf(pointers[i]);
					else
						delete pointers[i];
				}
			}
		}

		CTrieNode	*pointers[256];
	};


public:
						// Ctor
						CTrie()	{
							root	=	new CTrieNode;	// We always have a root
						}

						// Dtor
						~CTrie() {
							if (root != NULL) delete root;
						}

						// Insert an object into the trie
						void	insert(const char *key,valType val) {
							CTrieNode	*currentNode,*prevNode;

							for (prevNode=root,currentNode=root->pointers[(unsigned char) (*key++)];key[-1]!='\0';) {
								if (currentNode == NULL) {
									// We found our place in the trie
									prevNode->pointers[(unsigned char) key[-1]]	=	makeNode(new CTrieLeaf(key-1,val));

									return;
								} else if (isLeaf(currentNode)) {
									// We hit a leaf, push the other item down one level
									CTrieNode	*oLeaf	=	currentNode;
									CTrieLeaf	*cLeaf	=	getLeaf(currentNode);

									if (cLeaf->key[0] == '\0') {
										// We have a collision
										return;
									} else {
										cLeaf->key++;
									}

									currentNode												=	new CTrieNode;
									currentNode->pointers[(unsigned char) (*cLeaf->key)]	=	oLeaf;

									prevNode->pointers[(unsigned char) key[-1]]				= currentNode;
								} else {
									prevNode	=	currentNode;
									currentNode	=	currentNode->pointers[(unsigned char) (*key++)];
								}
							}

							prevNode->pointers[(unsigned char) key[-1]]	=	makeNode(new CTrieLeaf(key-1,val));
						}

						// Find an object in the trie
		int				find(const char *key,valType &val) const {
							CTrieNode	*cNode;
							CTrieLeaf	*cLeaf;

							for (cNode=root->pointers[(unsigned char) (*key)];;cNode=cNode->pointers[(unsigned char) (*key)]) {
								if (cNode == NULL) return FALSE;	// The item not found

								if (isLeaf(cNode)) {
									cLeaf	=	getLeaf(cNode);

									if (strcmp(key,cLeaf->key) == 0) {
										val	= cLeaf->val;
										return TRUE;
									} else
										return FALSE;
								}

								if (*key++ == '\0')	break;
							}

							return FALSE;
						}

		int				erase(const char *key,valType &val) {
							CTrieNode	*cNode,*pNode;
							CTrieLeaf	*cLeaf;

							for (pNode=root,cNode=root->pointers[(unsigned char) (*key)];;pNode=cNode,cNode=cNode->pointers[(unsigned char) (*key)]) {
								if (cNode == NULL) return FALSE;	// The item not found

								if (isLeaf(cNode)) {
									cLeaf	=	getLeaf(cNode);

									if (strcmp(key,cLeaf->key) == 0) {
										val	= cLeaf->val;
										pNode->pointers[(unsigned char) (*key)]	=	NULL;
										delete cLeaf;
										return TRUE;
									} else
										return FALSE;
								}

								if (*key++ == '\0')	break;
							}

							return FALSE;
						}

		void			destroy() {
							if (root != NULL)	destroyNode(root);
							root	=	NULL;
							delete this;
						}

		CTrieNode		*root;

private:

		void			destroyNode(CTrieNode *cNode) {

							if (isLeaf(cNode)) {
								CTrieLeaf	*cLeaf	=	getLeaf(cNode);
								delete cLeaf->val;
								delete cLeaf;
							} else {
								int	i;

								for (i=0;i<256;i++) {
									if (cNode->pointers[i] != NULL) {
										destroyNode(cNode->pointers[i]);
										cNode->pointers[i]	=	NULL;
									}
								}
								delete cNode;
							}
						}
};
















///////////////////////////////////////////////////////////////////////
// Class				:	CPqueue
// Description			:	Priority queue
// Comments				:
template <class ItemType,class PriorityType> class CPqueue  {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CPqueueItem
	// Description			:	Holds a priority queue item
	// Comments				:
	class	CPqueueItem	{
	public:
		ItemType		item;
		PriorityType	priority;
	};
public:
					CPqueue(int ss=100)	{
						stepSize	=	ss;
						maxItems	=	stepSize;
						numItems	=	1;
						allItems	=	new CPqueueItem[maxItems];
					}

		virtual		~CPqueue()	{
						delete [] allItems;
					}

		void		insert(ItemType item,PriorityType priority) {
						int i,j;

						// Expand the buffer
						if (numItems >= maxItems) {
							CPqueueItem	*newItems;
							maxItems	+=	stepSize;
							newItems	=	new CPqueueItem[maxItems];
							memcpy(newItems,allItems,numItems*sizeof(CPqueueItem));
							delete [] allItems;
							allItems	=	newItems;
							stepSize	*=	2;
						}
		
						// Insert the item
						i	= numItems++;
						j	= i >> 1;
						while ((i > 1) && (priority < allItems[j].priority)) {
							allItems[i]	=	allItems[j];
							i			=	j;
							j			=	i >> 1;

						}

						allItems[i].item			=	item;
						allItems[i].priority		=	priority;
					}

		
		int			getMax(ItemType *item,PriorityType &priority) {
						if (numItems <= 1) return FALSE;

						item[0]		=	allItems[1].item;
						priority	=	allItems[1].priority;
						return TRUE;
					}

		
		int			removeMax(ItemType *item,PriorityType &priority) {
						int			i = 1, j;
						CPqueueItem	*lItem;

						if (numItems <= 1) return FALSE;
					
						item[0]		=	allItems[1].item;
						priority	=	allItems[1].priority;
					
						numItems--;
						lItem		=	&allItems[numItems];

						while (i <= numItems / 2) {
							j = 2 * i;
							if (j >= numItems) break;

							if ((j < (numItems-1)) && (allItems[j].priority > allItems[j+1].priority))
								j++;

							if (allItems[j].priority > lItem->priority)
								break;

							allItems[i]	=	allItems[j];
							i			=	j;
						}
						allItems[i].priority			=	lItem->priority;
						allItems[i].item				=	lItem->item;
						return TRUE;
					}

	int				sanityCheck() {
						int i;
						for (i=0;i<numItems /2;i++) {
							int	j	=	i*2;
							if (allItems[j].priority < allItems[i].priority) return FALSE;
							j++;
							if (j < numItems)
								if (allItems[j].priority < allItems[i].priority) return FALSE;
						}
						return TRUE;
					}

private:
	CPqueueItem		*allItems;
	int				numItems,maxItems,stepSize;
};














///////////////////////////////////////////////////////////////////////
// Class				:	CMemPool
// Description			:	Memory pool for a particular class that's allocated frequently
// Comments				:
template <class T>	class CMemPool {
public:
	
						CMemPool(int itemsPerBank = 100) {
							this->itemsPerBank	=	itemsPerBank;	// The number of items to allocate at a time
							allocatedBanks		=	NULL;		
							freeItems			=	NULL;
						}

						~CMemPool() {
							T64		*cBank;

							while(allocatedBanks != NULL) {
								cBank			=	allocatedBanks;
								allocatedBanks	=	(T64 *) cBank->pointer;

								delete [] cBank;
							}
						}

				T		*newItem() {
							if (freeItems != NULL) {
								T			*cItem;
								cItem		=	(T *) freeItems;
								freeItems	=	(T64 *) freeItems->pointer;
								return cItem;	
							} else {
								T64			*cBank;
								int			i;
								T			*cItem;

								// Compute the number of words we want to allocate
								i				=	sizeof(T)*itemsPerBank/sizeof(T64)+1;

								// Insert the new bank into the linked list
								cBank			=	new T64[i];
								cBank->pointer	=	allocatedBanks;
								allocatedBanks	=	cBank;

								for (cBank++,i=itemsPerBank;i>0;i--) {
									cBank->pointer	=	freeItems;
									freeItems		=	cBank;
									cItem			=	(T *) cBank;
									cItem++;
									cBank			=	(T64 *) cItem;
								}

								cItem		=	(T *) freeItems;
								freeItems	=	(T64 *) freeItems->pointer;
								return cItem;	
							}
						}


				void	deleteItem(T *item) {
							T64	*tmp		=	(T64 *) item;

							tmp->pointer	=	freeItems;
							freeItems		=	tmp;
						}


	T64					*freeItems;			// Linked list of free items
	T64					*allocatedBanks;	// Linked list of allocated banks
	int					itemsPerBank;		// The number of items per bank
};

























///////////////////////////////////////////////////////////////////////
// Class				:	CMemStack
// Description			:	A stack based memory manager
// Comments				:
class CMemStack {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CMemPage
	// Description			:	This class contains a memory page
	// Comments				:
	class CMemPage {
	public:
			char			*memory;					// Points to the current free memory
			char			*base;						// Points to the base memory
			int				availableSize;				// The available number of bytes
			int				totalSize;					// The total size of the block
			CMemPage		*next;						// Points to the next free memory block
			CMemPage		*prev;						// points to the previous valid memory block
	};

public:
						CMemStack(int bs = 1 << 12) {
							pageSize	=	bs;
							firstPage	=	stack	=	memoryNewPage(pageSize);
						}

						~CMemStack() {
							while((stack = firstPage) != NULL) {
								firstPage	=	stack->next;
								
								memoryDeletePage(stack);
							}
						}

		inline void		*alloc(int size) {

							while(stack->availableSize < size) {

								if (stack->next == NULL) {
									CMemPage	*cPage				=	memoryNewPage(max(pageSize,size));
									cPage->prev						=	stack;
									stack->next						=	cPage;
								}

								stack								=	stack->next;
								stack->availableSize				=	stack->totalSize;
								stack->memory						=	stack->base;
							}


							void *ptr								=	stack->memory;
							stack->memory							=	stack->memory+size;
							stack->availableSize					-=	size;
							return	ptr;
						}

		inline void		save(T64 *data) {
							data[0].pointer			=	stack->memory;
							data[1].integer			=	stack->availableSize;
							data[2].pointer			=	stack;
						}

		inline void		restore(T64 *data) {
							stack					=	(CMemPage *) data[2].pointer;
							stack->availableSize	=	(int) data[1].integer;
							stack->memory			=	(char *) data[0].pointer;
						}

		CMemPage		*stack;
private:
		CMemPage		*firstPage;
		int				pageSize;

		CMemPage		*memoryNewPage(int size) {
							CMemPage	*newPage	=	new CMemPage;

							newPage->availableSize	=	size;
							newPage->totalSize		=	size;
							newPage->base			=	new char[size];
							newPage->memory			=	newPage->base;
							newPage->next			=	NULL;
							newPage->prev			=	NULL;

							return newPage;
						}

		void			memoryDeletePage(CMemPage *cPage) {
							delete [] cPage->base;
							delete cPage;
						}

};
















///////////////////////////////////////////////////////////////////////
// Class				:	CArray
// Description			:	Array
// Comments				:
template <class T> class CArray {
public:
						CArray(int ss = 100) {
							arraySize	=	ss;
							stepSize	=	ss;
							array		=	new T[arraySize];
							numItems	=	0;
						}

						~CArray() {
							delete [] array;
						}


		void			push(T item) {
							array[numItems++]	=	item;

							while (numItems >= arraySize) {
								T	*newArray	=	new T[arraySize+stepSize];

								memcpy(newArray,array,numItems*sizeof(T));

								arraySize		+=	stepSize;
								stepSize		*=	2;
								delete [] array;
								array			=	newArray;
							}
						}

		T				pop() {
							if (numItems == 0)	return 0;

							return array[--numItems];
						}


						// Array interface

		void			reserve(int sz) {

							if (sz > arraySize) {
								T       *newArray	=	new T[sz];

								 memcpy(newArray,array,arraySize*sizeof(T));

								 arraySize			=	sz;
								 delete [] array;
								 array				=	newArray;
							}
						}
						
		T				& operator[](int index) {
							assert(index < numItems);
							return array[index];
						}

		void			destroy() {
							int	i;

							for (i=0;i<numItems;i++) {
								delete array[i];
							}

							delete this;
						}

		T				*array;
		int				numItems;
		int				arraySize;
protected:
		int				stepSize;
};




///////////////////////////////////////////////////////////////////////
// Class				:	CList
// Description			:	List
// Comments				:	This class provides iteration functionality over an array
template <class T>	class CList : public CArray<T> {
public:
						CList() {
							currentItem	=	0;
						}


		T				first()	{
							if (CArray<T>::numItems == 0)	return 0;

							currentItem	=	0;
							return CArray<T>::array[currentItem];
						}

		T				last() {
							if (CArray<T>::numItems == 0)	return 0;

							currentItem	=	CArray<T>::numItems-1;
							return CArray<T>::array[currentItem];
						}

		T				next() {
							currentItem++;

							if (currentItem == CArray<T>::numItems)	return 0;

							return CArray<T>::array[currentItem];
						}

		T				prev() {
							currentItem--;

							if (currentItem == -1)			return 0;

							return CArray<T>::array[currentItem];
						}


private:
	int					currentItem;

};

#endif

