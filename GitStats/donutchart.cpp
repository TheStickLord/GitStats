#include "donutchart.h"
#include <QPainter>
#include <QtMath>

DonutChart::DonutChart(QWidget *parent)
    : QWidget(parent)
    , m_holeSize(0.5)
    , m_showLabels(true)
{
}

DonutChart::~DonutChart()
{
}

void DonutChart::setData(const QVector<QPair<QString, qreal>> &data)
{
    m_data = data;
    update();
}

void DonutChart::setHoleSize(double size)
{
    m_holeSize = size;
    update();
}

void DonutChart::setShowLabels(bool show)
{
    m_showLabels = show;
    update();
}

void DonutChart::addSlice(const QString &label, qreal value)
{
    m_data.append(qMakePair(label, value));
    update();
}

void DonutChart::clear()
{
    m_data.clear();
    update();
}

void DonutChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawDonut(painter);
    if (m_showLabels) {
        drawLabels(painter);
    }
}

void DonutChart::drawDonut(QPainter &painter)
{
    if (m_data.isEmpty()) {
        return;
    }

    qreal total = 0;
    for (const auto &item : m_data) {
        total += item.second;
    }

    if (total == 0) {
        return;
    }

    QRectF rect = QRectF(10, 10, width() - 20, height() - 20);
    qreal startAngle = 90 * 16;
    QColor colors[] = {
        QColor("#3498db"), QColor("#e74c3c"), QColor("#2ecc71"),
        QColor("#f39c12"), QColor("#9b59b6"), QColor("#1abc9c"),
        QColor("#e67e22"), QColor("#34495e")
    };

    for (int i = 0; i < m_data.size(); ++i) {
        qreal angleSpan = (m_data[i].second / total) * 360 * 16;
        painter.setBrush(colors[i % (sizeof(colors) / sizeof(colors[0]))]);
        painter.setPen(Qt::NoPen);
        painter.drawPie(rect, startAngle, angleSpan);
        startAngle -= angleSpan;
    }

    painter.setBrush(palette().window());
    painter.setPen(Qt::NoPen);
    qreal innerW = rect.width() * m_holeSize;
    qreal innerH = rect.height() * m_holeSize;
    QRectF innerRect(
        rect.x() + (rect.width() - innerW) / 2,
        rect.y() + (rect.height() - innerH) / 2,
        innerW,
        innerH
    );
    painter.drawEllipse(innerRect);
}

void DonutChart::drawLabels(QPainter &painter)
{
    if (m_data.isEmpty()) {
        return;
    }

    qreal total = 0;
    for (const auto &item : m_data) {
        total += item.second;
    }

    if (total == 0) {
        return;
    }

    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    qreal startAngle = 90 * 16;
    QColor colors[] = {
        QColor("#3498db"), QColor("#e74c3c"), QColor("#2ecc71"),
        QColor("#f39c12"), QColor("#9b59b6"), QColor("#1abc9c"),
        QColor("#e67e22"), QColor("#34495e")
    };

    QRectF rect = QRectF(10, 10, width() - 20, height() - 20);

    for (int i = 0; i < m_data.size(); ++i) {
        qreal angleSpan = (m_data[i].second / total) * 360 * 16;
        qreal midAngle = startAngle - angleSpan / 2;
        qreal midAngleDeg = midAngle / 16.0;

        qreal rad = qDegreesToRadians(midAngleDeg);
        qreal radius = qMin(rect.width(), rect.height()) / 2.0 * 0.7;
        qreal cx = rect.center().x();
        qreal cy = rect.center().y();
        qreal x = cx + radius * qCos(rad);
        qreal y = cy - radius * qSin(rad);

        qreal percentage = (m_data[i].second / total) * 100;
        QString label = QString("%1: %2%").arg(m_data[i].first).arg(percentage, 0, 'f', 1);
        painter.setPen(colors[i % (sizeof(colors) / sizeof(colors[0]))]);
        painter.drawText(QPointF(x, y), label);

        startAngle -= angleSpan;
    }
}
