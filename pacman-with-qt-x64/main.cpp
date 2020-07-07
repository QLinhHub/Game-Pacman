#include <time.h>

#include<QtWidgets/qapplication.h>

#include "Mainwnd.h"

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(0));

    Mainwnd bvn;
    //bvn.changeEcran(1);
    bvn.show();

    return app.exec();
}
