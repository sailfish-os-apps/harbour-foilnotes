/*
 * Copyright (C) 2018-2019 Jolla Ltd.
 * Copyright (C) 2018-2019 Slava Monich <slava@monich.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3. Neither the names of the copyright holders nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FOILNOTES_BASE_MODEL_H
#define FOILNOTES_BASE_MODEL_H

#include <QAbstractListModel>
#include <QColor>

class FoilNotesBaseModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int selected READ selectedCount NOTIFY selectedChanged)

public:
    class Note {
    public:
        static const QString PAGENR;
        static const QString COLOR;
        static const QString BODY;

        Note();
        Note(const Note& aNote);
        Note(int aPageNr, QColor aColor, QString aBody);

        bool equals(const Note& aNote) const;

        Note& operator=(const Note& aNote);
        bool operator==(const Note& aNote) const { return equals(aNote); }
        bool operator!=(const Note& aNote) const { return !equals(aNote); }

        QVariantMap toVariant() const;

    public:
        int iPageNr;
        QColor iColor;
        QString iBody;
    };

    FoilNotesBaseModel(QObject* aParent);

    virtual const Note* noteAt(int aRow) const = 0;
    virtual int selectedCount() const = 0;
    virtual bool selectedAt(int aRow) const = 0;
    virtual void setSelectedAt(int aRow, bool aSelected) = 0;
    virtual void emitSelectedChanged();

    Q_INVOKABLE virtual void addNote(QColor aColor, QString aBody) = 0;
    Q_INVOKABLE virtual void deleteNoteAt(int aIndex) = 0;
    Q_INVOKABLE virtual void setBodyAt(int aRow, QString aBody) = 0;
    Q_INVOKABLE virtual void setColorAt(int aRow, QColor aColor) = 0;
    Q_INVOKABLE virtual void deleteNotes(QList<int>) = 0;

    Q_INVOKABLE void selectAll();
    Q_INVOKABLE void clearSelection();
    Q_INVOKABLE QList<int> selectedRows() const;
    Q_INVOKABLE QVariantMap get(int aIndex) const;

    // QAbstractListModel
    Qt::ItemFlags flags(const QModelIndex& aIndex) const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void selectedChanged();
};

#endif // FOILNOTES_BASE_MODEL_H
