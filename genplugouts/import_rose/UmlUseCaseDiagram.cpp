
#include "UmlUseCaseDiagram.h"
#include "File.h"
#include "UmlItem.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <QByteArray>

void UmlUseCaseDiagram::import(File & f, UmlItem * parent)
{
    QByteArray s;

    if (f.read(s) != STRING)
        f.syntaxError(s, "use case diagram's name");

    QByteArray id;
    QByteArray ste;
    QByteArray doc;
    QHash<QByteArray, QByteArray*> prop;
    QByteArray s2;
    int k;

    do {
        k = f.readDefinitionBeginning(s2, id, ste, doc, prop);
    }
    while (id.isEmpty());

    UmlUseCaseDiagram * x;

    if (scanning) {
        if ((x = UmlBaseUseCaseDiagram::create(parent, s)) == 0) {
            UmlCom::trace("<br>cannot create use case diagram '" + s + "' in " +
                          parent->fullName());
            throw 0;
        }

        newItem(x, id);

        if (!doc.isEmpty())
            x->set_Description(doc);

        x->setProperties(prop);
    }
    else if ((x = (UmlUseCaseDiagram *) findItem(id, anUseCaseDiagram)) == 0) {
        UmlCom::trace("<br>unknown use case diagram '" + s + "' in " +
                      parent->fullName());
        throw 0;
    }

    f.unread(k, s2);
    // !!!!!!!!!!!!!!!!!!!!!!!
    f.skipBlock();
}

