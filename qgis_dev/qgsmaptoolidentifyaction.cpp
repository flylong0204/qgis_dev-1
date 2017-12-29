#include "qgsmaptoolidentifyaction.h"


QgsMapToolIdentifyAction::QgsMapToolIdentifyAction(QgsMapCanvas* canvas)
	: QgsMapToolIdentify(canvas)
	, mCanvas(nullptr)
{
}


QgsMapToolIdentifyAction::~QgsMapToolIdentifyAction(void)
{
}

void QgsMapToolIdentifyAction::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	QgsMapToolIdentify::identify(e->x(), e->y(), DefaultQgsSetting);
}
