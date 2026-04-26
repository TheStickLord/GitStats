#ifndef DONUTCHART_H
#define DONUTCHART_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QVector>
#include <QPair>

class DonutChart : public QWidget
{
    Q_OBJECT

public:
    explicit DonutChart(QWidget *parent = nullptr);
    ~DonutChart();

    QVector<QPair<QString, qreal>> data() const { return m_data; }
    void setData(const QVector<QPair<QString, qreal>> &data);

    double holeSize() const { return m_holeSize; }
    void setHoleSize(double size);

    bool showLabels() const { return m_showLabels; }
    void setShowLabels(bool show);

    void addSlice(const QString &label, qreal value);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawDonut(QPainter &painter);
    void drawLabels(QPainter &painter);

    QVector<QPair<QString, qreal>> m_data;
    double m_holeSize;
    bool m_showLabels;
};

#endif // DONUTCHART_H
