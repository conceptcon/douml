
#include "UmlDeploymentView.h"
#include "File.h"
#include "UmlPackage.h"

#include "UmlNode.h"
#include "UmlDeploymentDiagram.h"
#include "UmlCom.h"
//Added by qt3to4:
#include <QByteArray>
void UmlDeploymentView::import(File & f)
{
    QByteArray s;

    for (;;) {
        switch (f.read(s)) {
        case -1:
            f.eof();
            throw 0;

        case ')':
            return;

        case ATOM:
            if (s == "ProcsNDevs") {
                f.read("(");
                f.read("list");
                readObjects(f);
            }
            else
                f.skipNextForm();

            break;

        default:
            f.syntaxError(s);
        }
    }
}

void UmlDeploymentView::readObjects(File & f)
{
    for (;;) {
        QByteArray s;

        switch (f.read(s)) {
        case ')':
            return;

        case '(':
            break;

        default:
            f.syntaxError(s);
        }

        f.read("object");

        if (f.read(s) != ATOM)
            f.syntaxError(s, "an atom");

        if ((s == "Processor") || (s == "Device"))
            UmlNode::import(f, this, s.toLower());
        else if (s == "Process_Diagram")
            UmlDeploymentDiagram::import(f, this);
        else {
            //UmlCom::trace("<br>" + s + " in " + QByteArray(f.name()) + " NOT MANAGED by DeploymentView::readObject()");//[jasa] original line
            UmlCom::trace("<br>" + s + " in " + QByteArray(f.fileName().toLatin1()) + " NOT MANAGED by DeploymentView::readObject()");//[jasa] go from QFile to QString name to const char* for QByteArray constructor
            f.skipBlock();
        }
    }
}

UmlDeploymentView * UmlDeploymentView::create(UmlPackage * parent, const char * s, QByteArray bn)
{
    UmlDeploymentView * r = UmlBaseDeploymentView::create(parent, s);

    if (r != 0)
        r->_base_name = bn;

    return r;
}

void UmlDeploymentView::import(UmlPackage * parent, File & f)
{
    QByteArray s;
    QByteArray id;
    QByteArray ste;
    QByteArray doc;
    QHash<QByteArray, QByteArray*> prop;
    int k;

    for (;;) {
        k = f.readDefinitionBeginning(s, id, ste, doc, prop);

        if (s == "file_name") {
            if (f.read(s) != STRING)
                f.syntaxError(s, "a filename");

            File f2(s, f.fileName());

            if (! f2.open(QIODevice::ReadOnly))
                UmlCom::trace("<br>cannot open '" + s + "' referenced in "
                              + QByteArray(f.fileName().toLatin1()));//[jasa] QString to QByteArray conversion (.ascii())
            else {
                f2.read("(");
                f2.read("object");
                f2.read("Petal");
                f2.skipBlock();

                f2.read("(");
                f2.read("object");
                f2.read("Processes");
                import(parent, f2);
            }

            f.skipBlock();
            return;
        }
        else if (!id.isEmpty()) {
            f.unread(k, s);

            UmlDeploymentView * dv;

            if (scanning) {
                dv = UmlBaseDeploymentView::create(parent, "Deployment View");

                if (dv != 0)
                    newItem(dv, id);

                if (!ste.isEmpty())
                    dv->set_Stereotype(ste);

                if (!doc.isEmpty())
                    dv->set_Description(doc);

                dv->setProperties(prop);
            }
            else
                dv = (UmlDeploymentView *) findItem(id, aDeploymentView);

            if (dv == 0) {
                UmlCom::trace("<br>cannot create deployment view in '" +
                              parent->fullName() + "'");
                throw 0;
            }

            dv->import(f);
            return;
        }
        else
            f.skipNextForm();
    }
}

