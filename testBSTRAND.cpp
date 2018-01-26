#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "BSTRAND.h"

using namespace cop3530;

bool eqls( const size_t& a, const size_t& b ) { return a == b; }
bool compr( const size_t& a, const size_t& b ) { return ( a < b ); }

BSTRAND< size_t, size_t, compr ,eqls > tree{};

TEST_CASE( "CASE ONE: general operations", "[operations]" ) {
	SECTION( "insert // height // balance // size " ) {
		SECTION( "inserting constantly increasing/decreasing key priorities" ) {
			tree.clear();

			REQUIRE( tree.height() == 0 );
			REQUIRE( tree.balance() == 0 );
			REQUIRE( tree.size() == 0 );

			int size = 0;

			for( size_t i = 1; i < 500; ++i ) {
				tree.insert(i,i);

				size++;

				REQUIRE( tree.size() == size );
			}

			for( size_t i = 1000; i >= 500; --i ) {
				tree.insert(i,i);

				size++;

				REQUIRE( tree.size() == size );
			}
		}

		SECTION( "inserting varying key priorities" ) {
			tree.clear();

			tree.insert(10,10);
			REQUIRE(tree.size() == 1 );

			tree.insert(6,6);
			REQUIRE(tree.size() == 2 );

			tree.insert(14,14);
			REQUIRE(tree.size() == 3 );

			tree.insert(5,5);
			REQUIRE(tree.size() == 4 );

			tree.insert(4,4);
			REQUIRE(tree.size() == 5 );

			tree.insert(2,2);
			REQUIRE(tree.size() == 6 );

			tree.insert(3,3);
			REQUIRE(tree.size() == 7 );

			tree.insert(1,1);
			REQUIRE(tree.size() == 8 );

			tree.insert(8,8);
			REQUIRE(tree.size() == 9 );

			tree.insert(7,7);
			REQUIRE(tree.size() == 10 );

			tree.insert(9,9);
			REQUIRE(tree.size() == 11 );

			tree.insert(13,13);
			REQUIRE(tree.size() == 12 );

			tree.insert(20,20);
			REQUIRE(tree.size() == 13 );

			tree.insert(19,19);
			REQUIRE(tree.size() == 14 );

			tree.insert(18,18);
			REQUIRE(tree.size() == 15 );

			tree.insert(15,15);
			REQUIRE(tree.size() == 16 );

			tree.insert(16,16);
			REQUIRE(tree.size() == 17 );

			tree.insert(17,17);
			REQUIRE(tree.size() == 18 );
		}

		SECTION( "inserting duplicate key" ) {
			tree.clear();

			tree.insert(5,5);
			tree.insert(3,3);
			tree.insert(7,7);
			tree.insert(2,2);
			tree.insert(4,4);

			REQUIRE( tree.lookup(5) == 5 );
			REQUIRE( tree.size() == 5 );
			
			tree.insert(5,99);
			tree.insert(7,99);
			tree.insert(4,99);

			REQUIRE( tree.lookup(5) == 99 );
			REQUIRE( tree.lookup(7) == 99 );
			REQUIRE( tree.lookup(4) == 99 );
			REQUIRE( tree.size() == 5 );
		}
	}

	SECTION( "clear // is_empty" ) {
		SECTION( "after inserting constantly increasing/decreasing key priorities" ) {
			tree.clear();

			REQUIRE( tree.size() == 0 );

			REQUIRE( tree.is_empty() == true );

			for( size_t i = 1; i < 500; ++i )
				tree.insert(i,i);

			for( size_t i = 1000; i >= 500; --i )
				tree.insert(i,i);

			REQUIRE( tree.is_empty() == false );

			tree.clear();

			REQUIRE( tree.size() == 0 );

			REQUIRE( tree.is_empty() == true );
		}

		SECTION( "after inserting varying key priorities" ) {
			tree.clear();

			REQUIRE( tree.size() == 0 );

			REQUIRE( tree.is_empty() == true );

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

			REQUIRE( tree.is_empty() == false );

			tree.clear();

			REQUIRE( tree.size() == 0 );

			REQUIRE( tree.is_empty() == true );
		}
	}

	SECTION( "insert // lookup // contains" ) {
		SECTION( "after inserting constantly increasing/decreasing key priorities" ) {
			tree.clear();

			for( size_t i = 1; i <= 1000; ++i )
				REQUIRE( tree.contains(i) == false );

			tree.insert(50, 50);
			tree.insert(0,0);
			tree.insert(100,100);

			REQUIRE(tree.contains(50) == true );
			REQUIRE(tree.contains(0) == true );
			REQUIRE(tree.contains(100) == true );


			REQUIRE(tree.contains(1) == false );

			tree.clear();

			for( size_t i = 1; i < 500; ++i )
				tree.insert(i,i);

			for( size_t i = 1000; i >= 500; --i )
				tree.insert(i,i);

			for( size_t i = 1; i <= 1000; ++i ) {
				REQUIRE( tree.lookup(i) == i );

				REQUIRE( tree.contains(i) == true );
			}
		}

		SECTION( "after inserting varying key priorities" ) {
			tree.clear();

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

			REQUIRE( tree.lookup(1) == 1 );
			REQUIRE( tree.lookup(2) == 2 );
			REQUIRE( tree.lookup(3) == 3 );
			REQUIRE( tree.lookup(4) == 4 );
			REQUIRE( tree.lookup(5) == 5 );
			REQUIRE( tree.lookup(6) == 6 );
			REQUIRE( tree.lookup(7) == 7 );
			REQUIRE( tree.lookup(8) == 8 );
			REQUIRE( tree.lookup(9) == 9 );
			REQUIRE( tree.lookup(10) == 10 );
			REQUIRE( tree.lookup(13) == 13 );
			REQUIRE( tree.lookup(14) == 14 );
			REQUIRE( tree.lookup(15) == 15 );
			REQUIRE( tree.lookup(16) == 16 );
			REQUIRE( tree.lookup(17) == 17 );
			REQUIRE( tree.lookup(18) == 18 );
			REQUIRE( tree.lookup(19) == 19 );
			REQUIRE( tree.lookup(20) == 20 );

			REQUIRE( tree.contains(1) == true );
			REQUIRE( tree.contains(2) == true );
			REQUIRE( tree.contains(3) == true );
			REQUIRE( tree.contains(4) == true );
			REQUIRE( tree.contains(5) == true );
			REQUIRE( tree.contains(6) == true );
			REQUIRE( tree.contains(7) == true );
			REQUIRE( tree.contains(8) == true );
			REQUIRE( tree.contains(9) == true );
			REQUIRE( tree.contains(10) == true );
			REQUIRE( tree.contains(13) == true );
			REQUIRE( tree.contains(14) == true );
			REQUIRE( tree.contains(15) == true );
			REQUIRE( tree.contains(16) == true );
			REQUIRE( tree.contains(17) == true );
			REQUIRE( tree.contains(18) == true );
			REQUIRE( tree.contains(19) == true );
			REQUIRE( tree.contains(20) == true );

			REQUIRE( tree.contains(0) == false );
			REQUIRE( tree.contains(11) == false );
			REQUIRE( tree.contains(12) == false );
			REQUIRE( tree.contains(21) == false );
		}
	}

	SECTION( "remove" ) {
		SECTION( "after inserting constantly increasing/decreasing key priorities" ) {
			tree.clear();

			for( size_t i = 1; i < 500; ++i )
				tree.insert(i,i);

			for( size_t i = 1000; i >= 500; --i )
				tree.insert(i,i);

			for( size_t i = 1; i <= 1000; ++i ) {
				REQUIRE( tree.remove(i) == i );
				REQUIRE( tree.contains(i) == false );
			}
		}

		SECTION( "after inserting varying key priorities" ) {
			tree.clear();

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

			REQUIRE( tree.remove(10) == 10 );
			REQUIRE( tree.size() == 17 );
			
			REQUIRE( tree.remove(1) == 1 );
			REQUIRE( tree.size() == 16 );
			
			REQUIRE( tree.remove(2) == 2 );
			REQUIRE( tree.size() == 15 );
			
			REQUIRE( tree.remove(3) == 3 );
			REQUIRE( tree.size() == 14 );
			
			REQUIRE( tree.remove(4) == 4 );
			REQUIRE( tree.size() == 13 );
			
			REQUIRE( tree.remove(5) == 5 );
			REQUIRE( tree.size() == 12 );
			
			REQUIRE( tree.remove(14) == 14 );
			REQUIRE( tree.size() == 11 );
			
			REQUIRE( tree.remove(6) == 6 );
			REQUIRE( tree.size() == 10 );
			
			REQUIRE( tree.remove(7) == 7 );
			REQUIRE( tree.size() == 9 );
			
			REQUIRE( tree.remove(8) == 8 );
			REQUIRE( tree.size() == 8 );
			REQUIRE( tree.remove(15) == 15 );
			
			REQUIRE( tree.size() == 7 );
			REQUIRE( tree.remove(9) == 9 );
			REQUIRE( tree.size() == 6 );
			
			REQUIRE( tree.remove(13) == 13 );
			REQUIRE( tree.size() == 5 );
			REQUIRE( tree.remove(16) == 16 );
			
			REQUIRE( tree.size() == 4 );
			REQUIRE( tree.remove(17) == 17 );
			REQUIRE( tree.size() == 3 );
			
			REQUIRE( tree.remove(20) == 20 );
			REQUIRE( tree.size() == 2 );
			REQUIRE( tree.remove(18) == 18 );
			
			REQUIRE( tree.size() == 1 );
			REQUIRE( tree.remove(19) == 19 );

			
			REQUIRE( tree.contains(1) == false );
			REQUIRE( tree.contains(2) == false );
			REQUIRE( tree.contains(3) == false );
			REQUIRE( tree.contains(4) == false );
			REQUIRE( tree.contains(5) == false );
			REQUIRE( tree.contains(6) == false );
			REQUIRE( tree.contains(7) == false );
			REQUIRE( tree.contains(8) == false );
			REQUIRE( tree.contains(9) == false );
			REQUIRE( tree.contains(10) == false );
			REQUIRE( tree.contains(13) == false );
			REQUIRE( tree.contains(14) == false );
			REQUIRE( tree.contains(15) == false );
			REQUIRE( tree.contains(16) == false );
			REQUIRE( tree.contains(17) == false );
			REQUIRE( tree.contains(18) == false );
			REQUIRE( tree.contains(19) == false );
			REQUIRE( tree.contains(20) == false );

			REQUIRE( tree.height() == 0 );
			REQUIRE( tree.size() == 0 );
			REQUIRE( tree.balance() == 0 );
		}
	}
}

TEST_CASE( "CASE TWO: Iterators", "[iterator]" ) {
	SECTION( "iterating through list (non const)" ) {
		tree.clear();

		tree.insert( 10,10 );
		tree.insert( 7,7 );
		tree.insert( 13,13 );
		tree.insert( 6,6 );
		tree.insert( 8,8 );
		tree.insert( 11,11 );
		tree.insert( 14,14 );
		tree.insert( 1,1 );
		tree.insert( 20,20 );

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iter = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator end = tree.end();
		
		REQUIRE( (iter == end) == false );

		REQUIRE( iter -> value() == 1 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 6 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 7 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 8 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 10 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 11 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 13 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 14 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 20 );
		++iter;
		REQUIRE( (iter == end) == true );
	}

	SECTION( "iterating through list (const)" ) {
		tree.clear();

		tree.insert( 10,10 );
		tree.insert( 7,7 );
		tree.insert( 13,13 );
		tree.insert( 6,6 );
		tree.insert( 8,8 );
		tree.insert( 11,11 );
		tree.insert( 14,14 );
		tree.insert( 1,1 );
		tree.insert( 20,20 );

		BSTRAND< size_t, size_t, compr ,eqls > const Ctree = tree;

		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iter = Ctree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator end = Ctree.end();
		
		REQUIRE( (iter == end) == false );

		REQUIRE( iter -> value() == 1 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 6 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 7 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 8 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 10 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 11 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 13 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 14 );
		++iter;
		REQUIRE( (iter == end) == false );
		REQUIRE( iter -> value() == 20 );
		++iter;
		REQUIRE( (iter == end) == true );
	}

	SECTION( "preincrement // postincrement (const)" ) {
		tree.clear();

		tree.insert( 10,10 );
		tree.insert( 7,7 );
		tree.insert( 13,13 );
		tree.insert( 6,6 );
		tree.insert( 8,8 );
		tree.insert( 11,11 );
		tree.insert( 14,14 );
		tree.insert( 1,1 );
		tree.insert( 20,20 );

		BSTRAND< size_t, size_t, compr ,eqls > const Ctree = tree;

		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iter = Ctree.begin();

		REQUIRE( (iter++) -> value() == 1 );
		REQUIRE( iter -> value() == 6 );
		REQUIRE( iter -> key() == 6 );
		REQUIRE( (iter++) -> key() == 6 );
		REQUIRE( iter -> value() == 7 );
		REQUIRE( iter -> key() == 7 );
		REQUIRE( (++iter) -> value() == 8 );
		REQUIRE( iter -> value() == 8 );
		REQUIRE( iter -> key() == 8 );
		REQUIRE( (++iter) -> key() == 10 );
		REQUIRE( iter -> value() == 10 );
		REQUIRE( iter -> key() == 10 );
	}

	SECTION( "preincrement // postincrement (non-const)" ) {
		tree.clear();

		tree.insert( 10,10 );
		tree.insert( 7,7 );
		tree.insert( 13,13 );
		tree.insert( 6,6 );
		tree.insert( 8,8 );
		tree.insert( 11,11 );
		tree.insert( 14,14 );
		tree.insert( 1,1 );
		tree.insert( 20,20 );

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iter = tree.begin();

		REQUIRE( (iter++) -> value() == 1 );
		REQUIRE( iter -> value() == 6 );
		REQUIRE( iter -> key() == 6 );
		REQUIRE( (iter++) -> key() == 6 );
		REQUIRE( iter -> value() == 7 );
		REQUIRE( iter -> key() == 7 );
		REQUIRE( (++iter) -> value() == 8 );
		REQUIRE( iter -> value() == 8 );
		REQUIRE( iter -> key() == 8 );
		REQUIRE( (++iter) -> key() == 10 );
		REQUIRE( iter -> value() == 10 );
		REQUIRE( iter -> key() == 10 );
	}

	SECTION( "== // != // -> // copy and assignment (non-const)" ) {
		tree.clear();

		tree.insert( 10,10 );
		tree.insert( 7,7 );
		tree.insert( 13,13 );
		tree.insert( 6,6 );
		tree.insert( 8,8 );
		tree.insert( 11,11 );
		tree.insert( 14,14 );
		tree.insert( 1,1 );
		tree.insert( 20,20 );

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iterA = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator iterB = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator end = tree.end();

		REQUIRE( (iterA == iterB) == true );
		REQUIRE( (iterA == end) == false );
		REQUIRE( (iterA != iterB) == false );
		REQUIRE( (iterA != end) == true );

		++iterA;

		REQUIRE( (iterA == iterB) == false );
		REQUIRE( (iterA == end) == false );
		REQUIRE( (iterA != iterB) == true );
		REQUIRE( (iterA != end) == true );

		++iterB;

		REQUIRE( (iterA == iterB) == true );
		REQUIRE( (iterA == end) == false );
		REQUIRE( (iterA != iterB) == false );
		REQUIRE( (iterA != end) == true );

		iterA = end;

		REQUIRE( (iterA == iterB) == false );
		REQUIRE( (iterA == end) == true );
		REQUIRE( (iterA != iterB) == true );
		REQUIRE( (iterA != end) == false );

		for( int i = 0; i < 8; ++i )
			REQUIRE( ((iterB++) == iterA) == false );

		REQUIRE( (iterB == iterA) == true );
		REQUIRE( (iterB == end) == true );
		REQUIRE( (iterB != iterA) == false );
		REQUIRE( (iterB != end) == false );

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iterC = tree.begin();

		REQUIRE( iterC -> value() == 1 );
		iterC -> value() = 50;
		REQUIRE( tree.lookup(1) == 50 );
		REQUIRE( iterC -> value() == 50 );
		REQUIRE( iterC -> key() == 1 );

		// check for deep copy
		BSTRAND< size_t, size_t, compr ,eqls >::iterator iter_copy = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator iter_copied = tree.begin();

		++iter_copied;
		iter_copy = iter_copied;
		++iter_copied;

		REQUIRE( (iter_copy == iter_copied) == false );
		REQUIRE( iter_copied -> value() == 7 );
		REQUIRE( iter_copy -> value() == 6 );

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iter_copyCon = iter_copy;

		++iter_copy;

		REQUIRE( (iter_copyCon == iter_copy) == false );
		REQUIRE( iter_copy -> value() == 7 );
		REQUIRE( iter_copyCon -> value() == 6 );

		//empty tree
		tree.clear();

		BSTRAND< size_t, size_t, compr ,eqls >::iterator IT = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator END = tree.begin();

		REQUIRE( IT == END );
	}

	SECTION( "== // != // copy and assignment (const)" ) {
		tree.clear();

		tree.insert( 10,10 );
		tree.insert( 7,7 );
		tree.insert( 13,13 );
		tree.insert( 6,6 );
		tree.insert( 8,8 );
		tree.insert( 11,11 );
		tree.insert( 14,14 );
		tree.insert( 1,1 );
		tree.insert( 20,20 );

		BSTRAND< size_t, size_t, compr ,eqls > const Ctree = tree;

		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iterA = Ctree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iterB = Ctree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator end = Ctree.end();

		REQUIRE( (iterA == iterB) == true );
		REQUIRE( (iterA == end) == false );
		REQUIRE( (iterA != iterB) == false );
		REQUIRE( (iterA != end) == true );

		++iterA;

		REQUIRE( (iterA == iterB) == false );
		REQUIRE( (iterA == end) == false );
		REQUIRE( (iterA != iterB) == true );
		REQUIRE( (iterA != end) == true );

		++iterB;

		REQUIRE( (iterA == iterB) == true );
		REQUIRE( (iterA == end) == false );
		REQUIRE( (iterA != iterB) == false );
		REQUIRE( (iterA != end) == true );

		iterA = end;

		REQUIRE( (iterA == iterB) == false );
		REQUIRE( (iterA == end) == true );
		REQUIRE( (iterA != iterB) == true );
		REQUIRE( (iterA != end) == false );

		for( int i = 0; i < 8; ++i )
			REQUIRE( ((iterB++) == iterA) == false );

		REQUIRE( (iterB == iterA) == true );
		REQUIRE( (iterB == end) == true );
		REQUIRE( (iterB != iterA) == false );
		REQUIRE( (iterB != end) == false );

		// check for deep copy
		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iter_copy = Ctree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iter_copied = Ctree.begin();

		++iter_copied;
		iter_copy = iter_copied;
		++iter_copied;

		REQUIRE( (iter_copy == iter_copied) == false );
		REQUIRE( iter_copied -> value() == 7 );
		REQUIRE( iter_copy -> value() == 6 );

		BSTRAND< size_t, size_t, compr ,eqls >::const_iterator iter_copyCon = iter_copy;

		++iter_copy;

		REQUIRE( (iter_copyCon == iter_copy) == false );
		REQUIRE( iter_copy -> value() == 7 );
		REQUIRE( iter_copyCon -> value() == 6 );
	}
}

TEST_CASE( "CASE THREE: Rule of Five Verification", "[rule_of_five]" ) {
	SECTION( "Copy Constructor" ) {
		tree.clear();
		for( size_t i = 1; i < 500; ++i ) tree.insert(i,i);
		for( size_t i = 1000; i >= 500; --i ) tree.insert( i,i );

		BSTRAND< size_t, size_t, compr ,eqls > copy = tree;

		for( size_t i = 1; i <= 1000; ++i ) {
			REQUIRE( copy.lookup(i) == i );
			REQUIRE( copy.contains(i) == true );
		}

		REQUIRE( copy.size() == 1000 );

		//check for deep copy
		tree.remove(10);
		tree.remove(11);
		tree.insert(1001, 1001);

		REQUIRE( tree.contains(10) == false );
		REQUIRE( tree.contains(11) == false );
		REQUIRE( tree.contains(1001) == true );
		REQUIRE( copy.contains(10) == true );
		REQUIRE( copy.contains(11) == true );
		REQUIRE( copy.contains(1001) == false );
		REQUIRE( copy.size() != tree.size() );
		copy.insert(9999,9999);
		REQUIRE( copy.contains(9999) );
		REQUIRE( copy.remove(9999) == 9999 );
	}

	SECTION( "Overload Assignment" ) {
		tree.clear();
		for( size_t i = 1; i < 500; ++i ) tree.insert(i,i);
		for( size_t i = 1000; i >= 500; --i ) tree.insert( i,i );

		BSTRAND< size_t, size_t, compr ,eqls > assign{};
		for( size_t i = 1001; i < 1501; ++i ) assign.insert(i,i);
		for( size_t i = 2000; i >= 1500; --i ) assign.insert(i,i);

		assign = tree;

		for( size_t i = 1; i <= 1000; ++i ) {
			REQUIRE( assign.lookup(i) == i );
			REQUIRE( assign.contains(i) == true );
		}

		REQUIRE(assign.size() == 1000 );

		//check for deep copy
		tree.remove(10);
		tree.remove(11);
		tree.insert(1001, 1001);

		REQUIRE( tree.contains(10) == false );
		REQUIRE( tree.contains(11) == false );
		REQUIRE( tree.contains(1001) == true );
		REQUIRE( assign.contains(10) == true );
		REQUIRE( assign.contains(11) == true );
		REQUIRE( assign.contains(1001) == false );
		REQUIRE( assign.size() != tree.size() );
		assign.insert(9999,9999);
		REQUIRE( assign.contains(9999) );
		REQUIRE( assign.remove(9999) == 9999 );
	}

	SECTION( "Move Constructor" ) {
		tree.clear();
		for( size_t i = 1; i < 500; ++i ) tree.insert(i,i);
		for( size_t i = 1000; i >= 500; --i ) tree.insert( i,i );

		BSTRAND< size_t, size_t, compr ,eqls > move = std::move(tree);

		REQUIRE( tree.size() == 0 );
		tree.insert( 2,2 );
		tree.insert( 1,1 );
		tree.insert( 3,3 );
		REQUIRE( tree.size() == 3 );

		for( size_t i = 1; i <= 1000; ++i ) {
			REQUIRE( move.lookup(i) == i );
			REQUIRE( move.contains(i) == true );
		}

		REQUIRE( move.size() == 1000 );
		REQUIRE( move.remove(500) == 500 );
		REQUIRE( move.size() == 999 );
		move.insert(9999,9999);
		REQUIRE( move.contains(9999) );
		REQUIRE( move.remove(9999) == 9999 );
	}

	SECTION( "Overload Move Assignment" ) {
		tree.clear();
		for( size_t i = 1; i < 500; ++i ) tree.insert(i,i);
		for( size_t i = 1000; i >= 500; --i ) tree.insert( i,i );

		BSTRAND< size_t, size_t, compr ,eqls > move{};
		for( size_t i = 1001; i < 1501; ++i ) move.insert(i,i);
		for( size_t i = 2000; i >= 1500; --i ) move.insert(i,i);
		move = std::move(tree);

		REQUIRE( tree.size() == 0 );
		tree.insert( 2,2 );
		tree.insert( 1,1 );
		tree.insert( 3,3 );
		REQUIRE( tree.size() == 3 );

		for( size_t i = 1; i <= 1000; ++i ) {
			REQUIRE( move.lookup(i) == i );
			REQUIRE( move.contains(i) == true );
		}

		REQUIRE( move.size() == 1000 );
		REQUIRE( move.remove(500) == 500 );
		REQUIRE( move.size() == 999 );
		move.insert(9999,9999);
		REQUIRE( move.contains(9999) );
		REQUIRE( move.remove(9999) == 9999 );
	}
}

TEST_CASE( "CASE FOUR: error throwing", "[error]" ) {
	SECTION( "operations" ) {
		tree.clear();

		REQUIRE_THROWS( tree.remove(0) );
		REQUIRE_THROWS( tree.lookup(0) );

		tree.insert(1,1);

		REQUIRE_NOTHROW( tree.lookup(1) );
		REQUIRE_NOTHROW( tree.remove(1) );

		REQUIRE_THROWS( tree.remove(1) );
		REQUIRE_THROWS( tree.lookup(1) );

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

		REQUIRE_NOTHROW( tree.lookup(19) );
		REQUIRE_NOTHROW( tree.remove(19) );
		REQUIRE_NOTHROW( tree.lookup(10) );
		REQUIRE_NOTHROW( tree.remove(10) );
		REQUIRE_NOTHROW( tree.lookup(6) );
		REQUIRE_NOTHROW( tree.remove(6) );

		REQUIRE_THROWS( tree.lookup(19) );
		REQUIRE_THROWS( tree.remove(19) );
		REQUIRE_THROWS( tree.lookup(10) );
		REQUIRE_THROWS( tree.remove(10) );
		REQUIRE_THROWS( tree.lookup(6) );
		REQUIRE_THROWS( tree.remove(6) );

		REQUIRE_NOTHROW( tree.insert(14,100) );
		REQUIRE_NOTHROW( tree.insert(14,99) );
		REQUIRE_NOTHROW( tree.insert(8,100) );
		REQUIRE_NOTHROW( tree.insert(8,99) );

		tree.clear();

		REQUIRE_THROWS( tree.lookup(14) );
		REQUIRE_THROWS( tree.remove(14) );
		REQUIRE_THROWS( tree.lookup(8) );
		REQUIRE_THROWS( tree.remove(8) );
	}

	SECTION( "iterators" ) {
		tree.clear();

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iter = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator end = tree.end();

		REQUIRE_THROWS( ++iter );
		REQUIRE_THROWS( iter++ );
		REQUIRE_THROWS( ++end );
		REQUIRE_THROWS( end++ );
		REQUIRE_THROWS( iter -> value() );
		REQUIRE_THROWS( iter -> key() );
		REQUIRE_THROWS( end -> value() );
		REQUIRE_THROWS( end -> key() );
		REQUIRE_THROWS( *iter );
		REQUIRE_THROWS( *end );

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

		BSTRAND< size_t, size_t, compr ,eqls >::iterator iterB = tree.begin();
		BSTRAND< size_t, size_t, compr ,eqls >::iterator endB = tree.end();

		REQUIRE_NOTHROW( ++iterB );
		REQUIRE_NOTHROW( iterB++ );
		REQUIRE_THROWS( ++endB );
		REQUIRE_THROWS( endB++ );
		REQUIRE_NOTHROW( iterB -> value() );
		REQUIRE_NOTHROW( iterB -> key() );
		REQUIRE_THROWS( endB -> value() );
		REQUIRE_THROWS( endB -> key() );
		REQUIRE_NOTHROW( *iterB );
		REQUIRE_THROWS( *endB );

		for( ; iterB != endB; ++iterB ){
			REQUIRE_NOTHROW( iterB -> value() );
			REQUIRE_NOTHROW( iterB -> key() );
		}

		REQUIRE_THROWS( ++iterB );
		REQUIRE_THROWS( iterB++ );
		REQUIRE_THROWS( iterB -> value() );
		REQUIRE_THROWS( iterB -> key() );
		REQUIRE_THROWS( *iterB );
		REQUIRE_THROWS( *endB );
	}
}
