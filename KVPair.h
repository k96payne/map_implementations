#ifndef KVPAIR_H_
#define KVPAIR_H_

#include <iostream>

namespace cop3530 {

template< typename K, typename V >
class KVPair {
	public:
		KVPair( const K& k, V& v ) : k(k), v(v) { }
		const K& key( void ) { return k; }
		V& value( void ) { return v; }
	private:
		const K& k;
		V& v;
};

}

#endif