#ifndef BSTRAND_H_
#define BSTRAND_H_

#include <iostream>
#include <stdexcept>
#include <time.h> 
#include "KVPair.h"

namespace cop3530 {

template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
class BSTRAND {
	private:
		struct Node {
			Node * left, * right;
			K key;
			V value;
			KVPair< K, V >  kv; 

			Node( K k, V v ) : 
				left( nullptr ), right( nullptr ), key(k), value(v), kv( key, value ) { }	
		};

	public:
		// Iterator
		//--------------------------------------------------------//
		template< typename KT, typename VT >
		class BSTRAND_Iter {
			public:
				// Required Type Aliases
				//========================================================//
				using value_type = VT;
 				using reference = VT&;
 				using pointer = VT*;
				using difference_type = std::ptrdiff_t;
				using iterator_category = std::forward_iterator_tag;
				//========================================================//

				// Additional Type Aliases
				//========================================================//
				using self_type = BSTRAND_Iter;
				using self_reference = BSTRAND_Iter&;
				//========================================================//



				// Factories
				//========================================================//
				static BSTRAND_Iter create_begin( Node * begin, Node * root ) { 
					BSTRAND_Iter I( begin, root ); 
					return I; 
				}
				static BSTRAND_Iter create_end( Node * end, Node * root ) { 
					BSTRAND_Iter I( end, root ); 
					return I;
				}
				//========================================================//



				// Iterator Copy and Assignment
				//========================================================//
				self_reference operator=( BSTRAND_Iter const& I ) {
					if( &I == this ) { return *this; }
					curr = I.curr;
					treeRoot = I.treeRoot;
					temp = I.temp;
					return *this;
				}
				//========================================================//



				// Iterator Operations
				//========================================================//
				KVPair< KT, VT > operator*() const {
					if( curr == nullptr ) 
						throw std::runtime_error( "ERROR using reference : Iterator Exhausted: no such point" );

					return curr->kv;
				}

				KVPair< KT, VT > * operator->() const { 
					if( curr == nullptr ) 
						throw std::runtime_error( "ERROR using reference : Iterator Exhausted: no such point" );
					
					return &curr->kv; 
				}

				bool operator==( BSTRAND_Iter const& rhs ) const {
					return( (curr == rhs.curr) && (treeRoot == rhs.treeRoot) );
				}

				bool operator!=( BSTRAND_Iter const& rhs ) const {
					return( curr != rhs.curr || treeRoot != rhs.treeRoot );
				}

				self_reference operator++() {
					if( curr == nullptr ) 
						throw std::runtime_error( "ERROR using ++ : Iterator Exhausted: no such point" );

					Node * temp = curr;
					set_next( treeRoot, temp );
					return *this;
				}

				self_type operator++(int) {
					if( curr == nullptr ) 
						throw std::runtime_error( "ERROR using ++(int) : Iterator Exhausted: no such point" );

					self_type tmp(*this);
					++( *this );
					return tmp;
				}
				//========================================================//


			private:
				Node * curr, * treeRoot, * temp;

				Node * find_min( Node * root ) {
					if( root != nullptr ) {
						Node * curr = root;
						while( curr -> left != nullptr )
							curr = curr -> left;
						return curr;
					}
					else return root;
				}

				Node * find_max( Node * root ) {
					if( root != nullptr ) {
						Node * curr = root;
						while( curr -> right != nullptr )
							curr = curr -> right;
						return curr;
					}
					else return root;
				}

				Node * inorder_succ( Node * par, Node * pred ) {
					if( par == nullptr ) return nullptr;

					if( (par == pred) || ((temp = inorder_succ( par -> left, pred)) !=  nullptr) || 
										((temp = inorder_succ( par -> right, pred )) != nullptr) ) {
						if( temp != nullptr ) {
							if( par -> left == temp ) {
								curr = par;
								return nullptr;
							}
						}
						return par;
					}
					return nullptr;
				}

				void set_next( Node * root, Node * pred ) {
					if( pred -> right != nullptr ) {
						curr = find_min( pred -> right );
					}
					if( pred -> right == nullptr ) {
						if( find_max( root ) == pred ) {
							curr = nullptr;
						}
						else 
							inorder_succ( root, pred );
					}
				}

				// Iterator Constructor
				//--------------------------------------------------------//
				BSTRAND_Iter( Node * start, Node * root ) : curr( start ), treeRoot( root ), temp( nullptr ) { }

		}; //close iterator class

	public:
		// Constructor
		BSTRAND( void );

		// Copy Constructor
		BSTRAND( const BSTRAND& source );

		// Overload Assignment
		BSTRAND< K, V, cmpr, eqls >& operator=( const BSTRAND& source );

		// Move Constructor
		BSTRAND( BSTRAND&& source );

		// Overload Move Assignment
		BSTRAND< K, V, cmpr, eqls >& operator=( BSTRAND&& source );

		// Operations
		//========================================================//
		void insert( const K& key, V value ); //Insert value with specified key
		V remove( const K& k ); //Remove value with corresponding key
		V& lookup( const K& key ); //Find key-value pair and return reference to value
		bool contains( const K& key ); //Return true is key is found
		bool is_empty( void ); //Return true is map is empty
		bool is_full( void ); //Return true is map is full
		size_t size( void ); //Return the number of key-value pairs in map
		void clear( void ); //Remove all key-value pairs in map
		int height( void ); //Return the height of the tree
		int balance( void ); //Return the balance of the tree
		//========================================================//

		// Destructor
		~BSTRAND( void );

	private:
		Node * root;

		int max( int a, int b ) { return (a > b)? a : b; }

		int get_random( int n ) {
			srand(time(NULL));
			int r = rand() % n;
            return r;
        }

        // Recursive calls for operation implementations
		//--------------------------------------------------------//
		int do_height( Node *& root ) {
			if( root == nullptr ) return 0;
			else {
				int left = do_height( root -> left );
				int right = do_height( root -> right );

				return max( left, right ) + 1;
			}
		}

		int get_balance( Node *& root ) {
			if( root == nullptr ) return 0;
			else return do_height( root -> left ) - do_height( root -> right );
		}

		size_t get_size( Node *& root ) {
			if( root == nullptr ) return 0;
			else return ( get_size( root -> left ) 
						+ get_size( root -> right ) + 1 );
		}

		void do_clear( Node *& root ) {
			if( root == nullptr ) return;
			if( root -> left != nullptr ) do_clear( root -> left );
			if( root -> right != nullptr ) do_clear( root -> right );
			delete root;
			root = nullptr;
		}

		void rotate_right( Node *& root ) {
			Node * temp = root -> left;
			root -> left = temp -> right;
			temp -> right = root;
			root = temp;
		}

		void rotate_left( Node *& root ) {
			Node * temp = root -> right;
			root -> right = temp -> left;
			temp -> left = root;
			root = temp;
		}

		Node * do_insert_at_root( Node *& root, K key, V value ) {
			if( root == nullptr ) {
				root = new Node( key, value );
				return root;
			}

			if( cmpr(key, root -> key ) == true ) {
				do_insert_at_root( root -> left, key, value );
				rotate_right(root);
			}
			else {
				do_insert_at_root( root -> right, key, value );
				rotate_left(root);
			}

			return root;
		}

		Node * do_insert_at_leaf( Node *& root, K key, V value ) {
			if( root == nullptr ) {
				root = new Node( key, value );
				return root;
			}

			if( cmpr(key, root -> key ) == true ) 
				root -> left = do_insert_at_leaf( root -> left, key, value );
			else 
				root -> right = do_insert_at_leaf( root -> right, key, value );

			return root;
		}

		Node * do_remove( Node *& root, K key ) {
			if( root == nullptr ) return root;
			else if( cmpr( key, root -> key ) == true )
				root -> left = do_remove( root -> left, key );
			else if( cmpr( root -> key, key ) == true )
				root -> right = do_remove( root -> right, key );
			else {
				if( root -> left == nullptr && root -> right == nullptr ) {
					delete root;
					root = nullptr;
				}
				else if( root -> left == nullptr ) {
					Node * temp = root;
					root = root -> right;
					delete temp;
					temp = nullptr;
				}
				else if( root -> right == nullptr ) {
					Node * temp = root;
					root = root -> left;
					delete temp;
					temp = nullptr;
				}
				else {
					Node * inOrderSucc = root -> right;

					while( inOrderSucc -> left != nullptr ) 
						inOrderSucc = inOrderSucc -> left;

					root -> key = inOrderSucc -> key;
					root -> value = inOrderSucc -> value;

					root -> right = do_remove( root -> right, inOrderSucc -> key );
				}
			}
			return root;
		}

		Node * do_lookup( Node *& root, K key ) {
			if( root == nullptr )
				return root;
			if( eqls( key, root -> key ) == true )
				return root;
			if( cmpr(key, root -> key ) == true ) 
				return do_lookup( root -> left, key );
			else
				return do_lookup( root -> right, key );
		}

		void do_copy( Node *& currRoot, Node * sourceRoot ) {
			if( sourceRoot == nullptr ) currRoot = nullptr;
			else {
				currRoot = new Node( sourceRoot -> key, sourceRoot -> value );
				do_copy( currRoot -> left, sourceRoot -> left );
				do_copy( currRoot -> right, sourceRoot -> right );
			}
		}

		// Utility functions for begin() and end() calls
		//---------------------------------------------------------------//
		Node * find_min( void ) {
			if( root != nullptr ) {
				Node * curr = root;
				while( curr -> left != nullptr )
					curr = curr -> left;
				return curr;
			}
			else return root;
		}

		Node * find_min( void ) const {
			if( root != nullptr ) {
				Node * curr = root;
				while( curr -> left != nullptr )
					curr = curr -> left;
				return curr;
			}
			else return root;
		}

	public:
		// Iterator Creators
		//========================================================//
		//using size_t = std::size_t;
		using key_type = K;
		using value_type = V;
		using iterator = BSTRAND_Iter< key_type, value_type >;
		using const_iterator = BSTRAND_Iter< key_type, value_type >;

		const_iterator begin( void ) const { return const_iterator::create_begin( find_min(), this -> root ); }
		const_iterator end( void ) const { return const_iterator::create_end( nullptr, this -> root ); }
		iterator begin( void ) { return iterator::create_begin( find_min(), this -> root ); }
		iterator end( void ) { return iterator::create_end( nullptr, this -> root ); }
		//========================================================//
};

// CONSTRUCTOR
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
BSTRAND< K, V, cmpr, eqls >::BSTRAND( void ) : root( nullptr ) { }
//========================================================//



// COPY CONSTRUCTOR
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
BSTRAND< K, V, cmpr, eqls >::BSTRAND( const BSTRAND& source ) : root ( nullptr ) {
	do_copy( root, source.root );
}
//========================================================//



// OVERLOAD ASSIGNMENT
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
BSTRAND< K, V, cmpr, eqls >& BSTRAND< K, V, cmpr, eqls >::operator=( const BSTRAND& source ) {
	//Check for self assignment
	if( this == &source ) return *this;

	do_clear( root );
	do_copy( root, source.root );

	return *this;
}
//========================================================//



// MOVE CONSTRUCTOR
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
BSTRAND< K, V, cmpr, eqls >::BSTRAND( BSTRAND&& source ) : root( nullptr ) {
	root = source.root;
	source.root = nullptr;
}
//========================================================//



// OVERLOAD MOVE ASSIGNMENT
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
BSTRAND< K, V, cmpr, eqls >& BSTRAND< K, V, cmpr, eqls >::operator=( BSTRAND&& source ) {
	do_clear( root );

	root = source.root;
	source.root = nullptr;

	return *this;
}
//========================================================//



// DESTRUCTOR
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
BSTRAND< K, V, cmpr, eqls >::~BSTRAND( void ) {
	do_clear( root );
}
//========================================================//



// insert
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
void BSTRAND< K, V, cmpr, eqls >::insert( const K& key, V value ) {
	Node * temp = do_lookup(root, key);
	if( temp != nullptr ) temp -> value = value;
	else {
		if( get_random(get_size( root ) + 1 ) == 0 )
			do_insert_at_root( root, key, value );
		else
			do_insert_at_leaf( root, key, value );
	}
}
//========================================================//



// remove
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
V BSTRAND< K, V, cmpr, eqls >::remove( const K& key ) {
	Node * temp = do_lookup(root, key);
	if( temp == nullptr ) throw std::runtime_error( "ERROR: using BSTRAND< > remove(): key not found" );
	const V value = temp -> value;
	do_remove( root, key );
	return value;
}
//========================================================//


// lookup
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
V& BSTRAND< K, V, cmpr, eqls >::lookup( const K& key ) {
	Node * temp = do_lookup(root, key);
	if( temp == nullptr ) throw std::runtime_error( "ERROR: using BSTRAND< > lookup(): key not found" );
	return temp -> value;
}
//========================================================//


// contains
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
bool BSTRAND< K, V, cmpr, eqls >::contains( const K& key ) {
	Node * temp = do_lookup( root, key );
	if( temp == nullptr) return false;
	else return true;
}
//========================================================//



// is_empty
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
bool BSTRAND< K, V, cmpr, eqls >::is_empty( void ) {
	return root == nullptr;
}
//========================================================//



// is_full
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
bool BSTRAND< K, V, cmpr, eqls >::is_full( void ) {
	return false;
}
//========================================================//



// size
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
size_t BSTRAND< K, V, cmpr, eqls >::size( void ) {
	return get_size( root );
}
//========================================================//



// clear
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
void BSTRAND< K, V, cmpr, eqls >::clear( void ) {
	do_clear( root );
}
//========================================================//



// height
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
int BSTRAND< K, V, cmpr, eqls >::height( void ) {
	return do_height( root );
}
//========================================================//



// balance
//========================================================//
template< typename K, typename V, bool (*cmpr)(const K&, const K&), bool (*eqls)(const K&, const K&) >
int BSTRAND< K, V, cmpr, eqls >::balance( void ) {
	return get_balance( root );
}
//========================================================//

}

#endif