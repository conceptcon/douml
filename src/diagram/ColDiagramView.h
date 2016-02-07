// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef COLDIAGRAMVIEW_H
#define COLDIAGRAMVIEW_H

#include "DiagramView.h"
#include "ColMsg.h"
//Added by qt3to4:
#include <QTextStream>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>

class ColDiagramWindow;
class DiagramItem;
class UmlCanvas;
class OperationData;
class ToolCom;

class ColDiagramView : public DiagramView
{
protected:
    ColMsgList msgs;

public:
    ColDiagramView(QWidget * parent, UmlCanvas * canvas, int is);

    ColMsgList & get_msgs() {
        return msgs;
    };
    void update_msgs();
    void update_msg_supports();

    virtual void menu(const QPoint &) override;
    virtual void read(char *, char * k) override;
    virtual void save(QTextStream & st, QString & warning, bool copy) const override;

    void send(ToolCom * com);

private:
    ColDiagramWindow * window() const {
        return (ColDiagramWindow *) parent();
    };

protected:
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void dragEnterEvent(QDragEnterEvent *) override;
    virtual void dropEvent(QDropEvent *) override;
    virtual void dragMoveEvent(QDragMoveEvent *e) override;
};

#endif
