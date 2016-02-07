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

#ifndef DEPLOYMENTNODECANVAS_H
#define DEPLOYMENTNODECANVAS_H

#include "DiagramCanvas.h"
#include "Instance.h"
//Added by qt3to4:
#include <QTextStream>

#define DEPLOYMENTNODE_CANVAS_MIN_SIZE 32
#define DEPLOYMENTNODE_CANVAS_ADDED 10

class DeploymentNodeCanvas
    : public QObject, public DiagramCanvas, public Instance
{
    Q_OBJECT

protected:
    UmlColor itscolor;
    UmlColor used_color;
    Uml3States write_horizontally;
    bool horiz;
    Uml3States show_stereotype_properties;
    bool show_properties;
    QString iname;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    DeploymentNodeCanvas(BrowserNode * bn, UmlCanvas * canvas,
                         int x, int y, int id);
    virtual ~DeploymentNodeCanvas();

    virtual void delete_it() override;

    virtual void draw(QPainter & p);

    virtual UmlCode typeUmlCode() const override;
    virtual void delete_available(BooL & in_model, BooL & out_model) const override;
    virtual bool alignable() const override;
    virtual bool copyable() const override;
    virtual void remove(bool from_model) override;
    virtual void open() override;
    virtual void menu(const QPoint &) override;
    virtual QString may_start(UmlCode &) const override;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const override;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &) override;
    virtual aCorner on_resize_point(const QPoint & p) override;
    virtual void resize(aCorner c, int dx, int dy, QPoint &) override;
    virtual void resize(const QSize & sz, bool w, bool h) override;
    virtual bool move_with_its_package() const override;
    virtual void change_scale() override;
    virtual void history_save(QBuffer &) const override;
    virtual void history_load(QBuffer &) override;
    virtual void history_hide() override;

    virtual void save(QTextStream &, bool ref, QString & warning) const override;
    static DeploymentNodeCanvas * read(char *& , UmlCanvas * canvas, char *);

    void check_size();
    int min_width();
    int min_height();

    virtual QString get_name() const override;
    virtual void set_name(const QString & s) override;

    virtual BrowserNode * get_type() const override;
    virtual BrowserNode * new_type() override;
    virtual bool new_type_available() override;
    virtual BrowserNodeList & get_types(BrowserNodeList & r) const override;
    virtual void set_type(BrowserNode * t) override;

    virtual bool has_drawing_settings() const override;
    virtual void edit_drawing_settings(QList<DiagramItem *> &) override;
    virtual void clone_drawing_settings(const DiagramItem *src) override;
    void edit_drawing_settings();
    virtual bool get_show_stereotype_properties() const override;

    virtual void apply_shortcut(QString s);

private slots:
    void modified();	// canvas must be updated
    void deleted();	// the node/package is deleted
};

#endif
