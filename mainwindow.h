#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QToolButton>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QGroupBox>
#include <QTextEdit>
#include <QSlider>
#include <QPainter>
#include <QMap>
#include <QScrollArea>  // 添加头文件

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStatusBar *StatuBar;  //状态栏
    QLabel * StateTipLable;  //状态栏提示信息左框
    QLabel * StateInfoLable;  //状态栏提示信息
    QToolBar *ToolBar;  //工具栏
    QToolButton * DataStructureButton;
    QGraphicsScene *scene;        // 场景
    QVector<QPushButton*> algorithmButtons;  // 算法按钮组

    void init_Window();  //初始化窗体控件

private:
    void setupAlgorithmButtons();  // 设置算法按钮
    void initScene();             // 初始化场景
    void updateAlgorithmButtons(const QString& category);  // 更新算法按钮
    QList<QPair<QString, QStringList>> algorithmCategories;  // 修改为QList存储各分类
    int currentHighlightedLine;       // 当前高亮的行号
    QVector<int> codeExecutionSteps;  // 存储代码执行步骤
    void highlightCodeLine(int lineNumber);  // 高亮指定行
    void setupCodeHighlighting();      // 设置代码高亮
    QVector<QPair<int, QString>> algorithmSteps;  // 存储算法执行步骤和说明
    int currentStepIndex;                         // 当前执行步骤索引
    QString currentSelectedAlgorithm;  // 添加当前选中算法的记录

    QString loadAlgorithmFile(const QString& algorithmName);  // 添加新方法
    void executeAlgorithm(const QString& algorithmName, const QVector<int>& data);
    void updateVariableTable(int lineNumber);  // 添加新方法声明

private slots:
    void onAlgorithmSelected();   // 算法选择槽函数
    void onCategorySelected();    // 添加分类选择的槽函数
    void onStartClicked();            // 开始按钮点击
    void onNextStepClicked();         // 下一步按钮点击

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
