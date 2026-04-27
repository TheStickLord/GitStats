#ifndef CIRCULARCHART_H
#define CIRCULARCHART_H

#include "user.h"
#include <QWidget>
#include <qpainter.h>

namespace Ui {
class CircularChart;
}

class CircularChart : public QWidget
{
    Q_OBJECT

public:
    explicit CircularChart(QWidget *parent = nullptr);
    ~CircularChart();

    void SetUsers(std::vector<User> users);
    void AddUser(User user);
    void Clear();

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        QRectF r = rect().adjusted(10, 10, -10, -10);

        double total = 0;
        for (const User &v : values) total += v.Commits;

        if (total < 1) total++;

        int startAngle = 90 * 16;

        for (int i = 0; i < values.size(); i++) {
            int spanAngle = -360 * 16 * (values[i].Commits / total);

            QColor color = QColor::fromHsv(
                (i * 360) / values.size(), // hue
                180,            // saturation
                220             // value/brightness
                );

            p.setBrush(color);
            p.setPen(Qt::NoPen);
            p.drawPie(r, startAngle, spanAngle);

            startAngle += spanAngle;
        }

        // donut hole
        QRectF inner = r.adjusted(20, 20, -20, -20);
        p.setBrush(palette().window());
        p.drawEllipse(inner);
    }

private:
    Ui::CircularChart *ui;

    std::vector<User> values = {};
};

#endif // CIRCULARCHART_H
