#include "BSTRAND.h"

using namespace cop3530;
	
bool eqls( const size_t& a, const size_t& b ) { return a == b; }
bool compr( const size_t& a, const size_t& b ) { return ( a < b ); }

int main() {
	BSTRAND< size_t, size_t, compr ,eqls > tree{};

	// insert ======================//
	tree.insert(10,10);
	tree.insert(6,6);
	tree.insert(14,14);
	tree.insert(5,5);
	tree.insert(4,4);
	tree.insert(2,2);
	tree.insert(3,3);
	tree.insert(1,1);
	tree.insert(8,8);
	tree.insert(7,7);
	tree.insert(9,9);
	tree.insert(13,13);
	tree.insert(20,20);
	tree.insert(19,19);
	tree.insert(18,18);
	tree.insert(15,15);
	tree.insert(16,16);
	tree.insert(17,17);


	// remove ======================//
	tree.remove(10);
	tree.remove(5);
	tree.remove(13);
	tree.remove(17);


	// lookup ======================//
	tree.remove(1);
	tree.remove(16);
	tree.remove(14);
	tree.remove(7);


	// contains ====================//
	tree.contains(1);
	tree.contains(20);
	tree.contains(10);
	tree.contains(17);


	// is_empty ====================//
	tree.is_empty();
	

	// is_full =====================//
	tree.is_full();


	// size ========================//
	tree.size();


	// height ======================//
	tree.height();


	// balance =====================//
	tree.balance();


	// iterators ===================//
	BSTRAND< size_t, size_t, compr ,eqls >::iterator iter = tree.begin();
	BSTRAND< size_t, size_t, compr ,eqls >::iterator end = tree.end();

	iter -> value() = 20;
	*iter;

	for( ; iter != end; ++iter )  { }

	BSTRAND< size_t, size_t, compr ,eqls > const Ctree = tree;

	BSTRAND< size_t, size_t, compr ,eqls >::const_iterator Citer = Ctree.begin();
	BSTRAND< size_t, size_t, compr ,eqls >::const_iterator Cend = Ctree.end();

	for( ; Citer != Cend; ++Citer )  { }


	// rule of five ===================//
	BSTRAND< size_t, size_t, compr ,eqls > copy = tree;
	
	BSTRAND< size_t, size_t, compr ,eqls > assign{};
	for( size_t i = 1001; i < 1501; ++i ) assign.insert(i,i);
	for( size_t i = 2000; i >= 1500; --i ) assign.insert(i,i);

	assign = tree;

	BSTRAND< size_t, size_t, compr ,eqls > move = std::move(tree);

	BSTRAND< size_t, size_t, compr ,eqls > moveA{};
	for( size_t i = 1001; i < 1501; ++i ) moveA.insert(i,i);
	for( size_t i = 2000; i >= 1500; --i ) moveA.insert(i,i);
	moveA = std::move(move);
	

	// clear ==========================//
	tree.clear();

	return 0;
}