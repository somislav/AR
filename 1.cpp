#include <iostream>
#include <vector>

using namespace std;

using Clause = vector<int>;
using NormalForm = vector<Clause>;

int p(int i) { return 3 * i + 1; }
int q(int i) { return 3 * i + 2; }
int r(int i) { return 3 * i + 3;} 

int varCount = 0;
NormalForm formula;

void clause(const Clause& c) {
	formula.push_back(c);
	for(auto& literal : c)
		varCount = max(varCount, abs(literal));
}

void R(int i, int j) {
	clause({ -r(j), r(i) }); 
	clause({ r(j), -r(i) });

	clause({ -q(j), q(i), r(i) });
	clause({ -q(j), -q(i), -r(i) });
	clause({ q(j), q(i), -r(i) });
	clause({ q(j), -q(i), r(i) });

    clause({ p(j), -p(i), q(i) });
    clause({ p(j), -p(i), r(i) });
    clause({ p(j), p(i), -q(i), -r(i) }); 
    clause({ -p(j), p(i), q(i) });
    clause({ -p(j), p(i), r(i) });
    clause({ -p(j), -p(i), -q(i), -r(i) }); 
    
    
    
}

void nJ(int i, int j) {
	clause({ p(i), p(j), q(i), q(j), r(i), r(j) });
    clause({ p(i), p(j), q(i), q(j), -r(i), -r(j) });
	clause({ p(i), p(j), -q(i), -q(j), r(i), r(j) });
	clause({ p(i), p(j), -q(i), -q(j), -r(i), -r(j) });
	clause({ -p(i), -p(j), q(i), q(j), r(i), r(j) });
    clause({ -p(i), -p(j), q(i), q(j), -r(i), -r(j) });
	clause({ -p(i), -p(j), -q(i), -q(j), r(i), r(j) });
	clause({ -p(i), -p(j), -q(i), -q(j), -r(i), -r(j) });
}


int main() {
	R(0, 1);
	R(1, 2);
	R(2, 3);
	R(3, 4);
    R(4, 5);
    R(5, 6);
    R(6, 7);
    R(7, 8);
	nJ(0, 8);
	
	cout << "p cnf " << varCount << ' ' << formula.size() << endl;
	for(auto& c : formula) {
		for(auto& l : c)
			cout << l << ' ';
		cout << 0 << endl;
	}
	return 0;
}