/** \file Keyvec.h
 *
 * \date Jun 4, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#ifndef KEYVEC_H_
#define KEYVEC_H_

#include <vector>
#include "Keyval.h"

template<class T>
class Keyvec: public Keyval<T> {
public:
	Keyvec(const string name, bool set, vector<T> xarg) :
		arg(xarg), Keyval<T>(name, set) {};
	virtual ~Keyvec();
	virtual bool get(vector<T> &t) {t=arg; return this->isset;};
	virtual void set(vector<T> &t) {arg=t; this->isset=true;};
	virtual ostream &print(ostream &o);

protected:
	vector<T> arg;
};

#endif /* KEYVEC_H_ */
