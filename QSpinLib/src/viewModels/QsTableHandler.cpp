#include "qspin/viewModels/QsTableHandler.h"

QString QsTableColumn::text() const{ return _text;}

void QsTableColumn::setText(QString value) {
    SET_QPROP(_text, value,
              _text_role =  QString("%1_role").arg(text()).remove(trim());
            emit textChanged();
    )
}
