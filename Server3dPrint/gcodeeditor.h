#ifndef GCODEEDITOR_H
#define GCODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class GcodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    GcodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(GcodeEditor *editor) : QWidget(editor) {
        gcodeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(gcodeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        gcodeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    GcodeEditor *gcodeEditor;
};

#endif // GCODEEDITOR_H
