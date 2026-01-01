#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "bookmessageeditview.h"
#include "bookmessageview.h"
#include"borrowbookeditview.h"
#include"borrowselect.h"
#include"loginview.h"
#include"readerfileeditview.h"
#include"readerfileview.h"
#include"recordview.h"
#include"welcomeview.h"
#include"overduechecker.h"







QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

      OverdueChecker *m_overdueChecker;

private slots:
    void on_btBack_clicked();

    void on_btLogout_clicked();

    void on_stackedWidget_currentChanged(int arg1);



public slots:
    void goLoginView();
    void goWelcomeView();
    void goBookMessageEditView(int rowNo);
    void goBookMessageView();
    void goBorrowBookEditView(int rowNo);
    void goBorrowSelectView();
    void goReaderFileEditView(int rowNo);
    void goReaderFileView();
    void goRecordView();
    void goPreviousView();


    //doubaodaima
    void handleOverdue(int recordId, const QString &readerName,
                       const QString &bookName, const QDateTime &dueDate);
    //void checkOverdueRecords(QSqlDatabase &db);


private:
    void pushWidgetToStackView(QWidget *widget);
    Ui::MasterView *ui;
    loginView *login_view;
    bookMessageEditView * book_message_edit_view;
    BookMessageView * book_message_view;
    borrowBookEditView * borrow_book_edit_view;
    BorrowSelect * borrow_select;
    readerFileEditView*  reader_file_edit_view;
    ReaderFileView* reader_file_view;
    RecordView* record_view;
    WelcomeView* welcome_view;

};
#endif // MASTERVIEW_H
