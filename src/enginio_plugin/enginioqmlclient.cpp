/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://qt.digia.com/contact-us
**
** This file is part of the Enginio Qt Client Library.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
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
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "enginioqmlacloperation.h"
#include "enginioqmlclient.h"
#include "enginioqmlidentityauthoperation.h"
#include "enginioqmlobjectoperation.h"
#include "enginioqmlqueryoperation.h"

#include <QUrl>
#include <QDebug>

/*!
 * \qmltype Client
 * \instantiates EnginioQmlClient
 * \inqmlmodule enginio-plugin
 * \brief Enginio client inteface to access the service.
 *
 * Client is used in all communication with the Enginio backend. The backend
 * application is identified with backend ID and secret.
 *
 * It also provides methods for creating operation objects dynamically.
 */

/*!
 * \qmlproperty string Client::backendId
 * Enginio backend ID. This can be obtained from the Enginio dashboard.
 */

/*!
 * \qmlproperty string Client::backendSecret
 * Enginio backend secret. This can be obtained from the Enginio dashboard.
 */

/*!
 * \qmlproperty string Client::apiUrl
 * Enginio backend URL. Normally there's no need to change the default URL.
 */

/*!
 * \qmlproperty string Client::sessionToken
 * Token of currently authenticated session. This is empty string if there's no
 * authenticated session.
 */

/*!
 * \qmlsignal Client::sessionAuthenticated()
 * This signal is emitted when the user logs in.
 */

/*!
 * \qmlsignal Client::sessionTerminated()
 * This signal is emitted when the user logs out.
 */


EnginioQmlClient::EnginioQmlClient(const QString &backendId,
                                   const QString &backendSecret,
                                   QObject *parent) :
    EnginioClient(backendId, backendSecret, parent)
{
}

void EnginioQmlClient::componentComplete()
{
    emit clientInitialized();
}

QString EnginioQmlClient::apiUrlAsString() const
{
    return apiUrl().toString();
}

void EnginioQmlClient::setApiUrlFromString(const QString &apiUrl)
{
    setApiUrl(QUrl(apiUrl));
}

/*!
 * \qmlmethod Client::createObjectOperation(ObjectModel model = 0)
 * Returns new \l ObjectOperation which can be used to create new objects on
 * backend or read, update or delete existing objects. If \a model is specified,
 * when operation finishes corresponding object in \a model will be updated.
 * Returned operation can be deleted with \c destroy().
 */
EnginioQmlObjectOperation * EnginioQmlClient::createObjectOperation(
        EnginioQmlObjectModel *model)
{
    return new EnginioQmlObjectOperation(this, model);
}

/*!
 * \qmlmethod Client::createQueryOperation(ObjectModel model = 0)
 *
 * Returns new \l QueryOperation which can be used to query objects from
 * backend. If \a model is specified, when operation finishes any objects
 * fetched from backend will be added to \a model. Returned operation can be
 * deleted with \c destroy().
 */
EnginioQmlQueryOperation * EnginioQmlClient::createQueryOperation(
        EnginioQmlObjectModel *model)
{
    return new EnginioQmlQueryOperation(this, model);
}

/*!
 * \qmlmethod Client::createIdentityAuthOperation()
 *
 * Returns new \l IdentityAuthOperation which can be used to authenticate user
 * with Enginio backend. Returned operation can be deleted with \c destroy().
 */
EnginioQmlIdentityAuthOperation * EnginioQmlClient::createIdentityAuthOperation()
{
    return new EnginioQmlIdentityAuthOperation(this);
}

/*!
 * \qmlmethod Client::createAclOperation()
 *
 * Returns new \l AclOperation which can be used to read and modify permissions
 * of Enginio objects. Returned operation can be deleted with \c destroy().
 */
EnginioQmlAclOperation * EnginioQmlClient::createAclOperation()
{
    return new EnginioQmlAclOperation(this);
}
