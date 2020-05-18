/*
 * Peony-Qt's Library
 *
 * Copyright (C) 2019, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#ifndef FILEUNTRASHOPERATION_H
#define FILEUNTRASHOPERATION_H

#include "peony-core_global.h"
#include "file-operation.h"

namespace Peony {

/*!
 * \brief The FileUntrashOperation class
 * \bug
 * can not restore the files which's parents has chinese.
 */
class PEONYCORESHARED_EXPORT FileUntrashOperation : public FileOperation
{
    Q_OBJECT
public:
    explicit FileUntrashOperation(QStringList uris, QObject *parent = nullptr);

    void run() override;
    std::shared_ptr<FileOperationInfo> getOperationInfo() override {
        return m_info;
    }

protected:
    void cacheOriginalUri();
    const QString handleDuplicate(const QString &uri);

private:
    GFileCopyFlags m_default_copy_flag = GFileCopyFlags(G_FILE_COPY_NOFOLLOW_SYMLINKS|
                                         G_FILE_COPY_ALL_METADATA);

    QStringList m_uris;
    QHash<QString, QString> m_restore_hash;
    std::shared_ptr<FileOperationInfo> m_info = nullptr;

    ResponseType m_pre_handler = Invalid;
};

}

#endif // FILEUNTRASHOPERATION_H
