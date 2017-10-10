#ifndef PIECESLIST_H
#define PIECESLIST_H

#include <QListWidget>

class PiecesList : public QListWidget
{
    Q_OBJECT

public:
    explicit PiecesList(int pieceSize, QWidget *parent = 0);
    void addPiece(QPixmap pixmap, QPoint location);

    static QString puzzleMimeType() { return QStringLiteral("image/x-puzzle-piece"); }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

    int m_PieceSize;
};

#endif // PIECESLIST_H
