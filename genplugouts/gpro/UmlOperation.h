#ifndef _UMLOPERATION_H
#define _UMLOPERATION_H


#include "UmlBaseOperation.h"
#include <QByteArray>

// This class manages 'operations', notes that the class 'UmlClassItem'
// is a mother class of all the class's children.
//
// You can modify it as you want (except the constructor)
class UmlOperation : public UmlBaseOperation {
  public:
    UmlOperation(void * id, const QByteArray & n) : UmlBaseOperation(id, n) {};

};

#endif
