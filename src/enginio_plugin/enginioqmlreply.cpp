/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtEnginio module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "enginioqmlreply.h"
#include "enginioqmlclient_p.h"
#include "enginioqmlclient.h"
#include <Enginio/private/enginioreply_p.h>
#include <QtQml/qjsvalue.h>
#include <QtQml/qqmlengine.h>
#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>

QT_BEGIN_NAMESPACE

/*!
  \qmltype EnginioReply
  \instantiates EnginioQmlReply
  \inqmlmodule Enginio 1
  \ingroup engino-qml
  \target EnginioModelQml

  \brief A reply to any \l Enginio request.
*/

/*!
  \qmlproperty QJsonObject Enginio1::EnginioReply::data
  The data of this reply.
*/

/*!
  \qmlproperty EnginioReply::ErrorTypes Enginio1::EnginioReply::errorType
  The type of error (if any) of this reply.
*/

/*!
  \qmlproperty QNetworkReply::NetworkError Enginio1::EnginioReply::networkError
  The network error (if any).
*/

/*!
  \qmlproperty string Enginio1::EnginioReply::errorString
  The error message if this reply was an error.
*/

/*!
  \qmlproperty int Enginio1::EnginioReply::backendStatus
  The backend status code.
*/

class EnginioQmlReplyPrivate : public EnginioReplyBasePrivate
{
    QMetaObject::Connection _orphanConnection;

    Q_DECLARE_PUBLIC(EnginioQmlReply)
public:
    EnginioQmlReplyPrivate(EnginioQmlClientPrivate *client, QNetworkReply *reply)
        : EnginioReplyBasePrivate(client, reply)
    {
        Q_ASSERT(client);
    }

    void emitFinished()
    {
        Q_Q(EnginioQmlReply);
        q->setParent(0);
        QQmlEngine::setObjectOwnership(q, QQmlEngine::JavaScriptOwnership);
        emit q->finished(static_cast<EnginioQmlClientPrivate*>(_client)->jsengine()->newQObject(q));
    }

    QJSValue data() const
    {
        if (_data.isEmpty() && _nreply->isFinished())
            _data = _nreply->readAll();

        return static_cast<EnginioQmlClientPrivate*>(_client)->fromJson(_data);
    }
};


EnginioQmlReply::EnginioQmlReply(EnginioQmlClientPrivate *parent, QNetworkReply *reply)
    : EnginioReplyBase(parent, reply, new EnginioQmlReplyPrivate(parent, reply))
{}

EnginioQmlReply::~EnginioQmlReply()
{}

QJSValue EnginioQmlReply::data() const
{
    Q_D(const EnginioQmlReply);
    return d->data();
}

/*!
  \internal
*/
void EnginioQmlReply::emitFinished()
{
    Q_D(EnginioQmlReply);
    d->emitFinished();
}

QT_END_NAMESPACE
