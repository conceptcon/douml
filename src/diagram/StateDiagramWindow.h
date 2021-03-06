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

#ifndef STATEDIAGRAMWINDOW_H
#define STATEDIAGRAMWINDOW_H

#include "DiagramWindow.h"

class QToolButton;
class QSpinBox;

class StateDiagramView;
class BrowserStateDiagram;

class StateDiagramWindow : public DiagramWindow
{
    Q_OBJECT

protected:
    StateDiagramView * view;
    QToolButton * addState;
    QToolButton * addEntryPoint;
    QToolButton * addExitPoint;
    QToolButton * addInitial;
    QToolButton * addFinal;
    QToolButton * addTerminate;
    QToolButton * addDeepHistory;
    QToolButton * addShallowHistory;
    QToolButton * addJunction;
    QToolButton * addChoice;
    QToolButton * addFork;
    QToolButton * addJoin;
    QToolButton * addTransition;
    QToolButton * addPackage;
    QToolButton * addFragment;
    QToolButton * addRegion;
    QToolButton * addAction;
    QToolButton * addSignalIn;
    QToolButton * addSignalOut;
    //QToolButton * dependency;
    QToolButton * note;
    QToolButton * anchor;
    QToolButton * text;
    QToolButton * image;

public:
    StateDiagramWindow(const QString & s, BrowserStateDiagram * b, int id = -1);
    virtual ~StateDiagramWindow();

    virtual DiagramView * get_view() const override;

    virtual void hit_button(UmlCode, QToolButton *) override;

protected slots:
    void hit_state();
    void hit_package();
    void hit_fragment();
    void hit_entryPoint();
    void hit_exitPoint();
    void hit_initial();
    void hit_final();
    void hit_terminate();
    void hit_deepHistory();
    void hit_shallowHistory();
    void hit_junction();
    void hit_choice();
    void hit_fork();
    void hit_join();
    void hit_region();
    void hit_action();
    void hit_signalin();
    void hit_signalout();
    void hit_transition();
    //void hit_dependency();
    void hit_note();
    void hit_anchor();
    void hit_text();
    void hit_image();
};

#endif
