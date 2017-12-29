#ifndef QGSMAPTOOLIDENTIFYACTION_H
#define QGSMAPTOOLIDENTIFYACTION_H

#include <qgsmaptoolidentify.h>
#include <qgsmapcanvas.h>

class QgsMapToolIdentifyAction :
	public QgsMapToolIdentify
{
public:
	QgsMapToolIdentifyAction(QgsMapCanvas* canvas);
	~QgsMapToolIdentifyAction(void);

	void canvasReleaseEvent(QgsMapMouseEvent* e) override;

private:
	QgsMapCanvas* mCanvas;
};

#endif