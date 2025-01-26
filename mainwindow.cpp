#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithmanager.h"

#include <QFile>
#include <QTimer>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);  // 创建场景
    init_Window();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_Window()
{
    resize(1000,700);
    // 这里是状态栏初始化
    StatuBar = new QStatusBar(this);
    StateTipLable = new QLabel(this);
    StateInfoLable = new QLabel(this);
    this->setStatusBar(StatuBar);
    StateTipLable->setText("提示信息：");
    StateInfoLable->setText("这里是提示信息");
    StatuBar->addWidget(StateTipLable);
    StatuBar->addWidget(StateInfoLable);

    // 这里是工具栏初始化
    ToolBar = new QToolBar(this);
    this->addToolBar(Qt::TopToolBarArea, ToolBar);

    // 初始化算法分类（按难度排序）
    algorithmCategories = {
        qMakePair(QString("基础算法"), QStringList({"冒泡排序", "选择排序", "插入排序", "顺序查找", "二分查找"})),
        qMakePair(QString("树结构"), QStringList({"二叉树遍历", "二叉搜索树", "AVL树", "红黑树"})),
        qMakePair(QString("排序算法"), QStringList({"快速排序", "归并排序", "堆排序", "希尔排序", "计数排序"})),
        qMakePair(QString("图论算法"), QStringList({"最短路径", "最小生成树", "拓扑排序", "关键路径"})),
        qMakePair(QString("高级算法"), QStringList({"动态规划", "贪心算法", "回溯算法", "分治算法"}))
    };

    // 修改工具栏分类按钮的创建方式
    for (const auto &category : algorithmCategories)
    {
        QToolButton *btn = new QToolButton(this);
        btn->setText(category.first);
        btn->setToolTip(category.first + "演示");
        btn->setMinimumSize(80, 40);
        connect(btn, &QToolButton::clicked, this, &MainWindow::onCategorySelected);
        ToolBar->addWidget(btn);
    }

    // 添加工具栏分隔符
    ToolBar->addSeparator();

    // 添加运行控制按钮
    QStringList controls = {"开始", "暂停", "重置", "下一步"};
    for (const QString &control : controls)
    {
        QToolButton *btn = new QToolButton(this);
        btn->setText(control);
        btn->setMinimumSize(60, 40);
        ToolBar->addWidget(btn);
        
        // 连接按钮信号
        if (control == "开始") {
            connect(btn, &QToolButton::clicked, this, &MainWindow::onStartClicked);
        } else if (control == "下一步") {
            connect(btn, &QToolButton::clicked, this, &MainWindow::onNextStepClicked);
        }
    }

    // 设置场景
    ui->displayArea->setScene(scene);
    ui->displayArea->setRenderHint(QPainter::Antialiasing);  // 添加抗锯齿

    // 设置日志区域
    ui->logArea->setPlaceholderText("运行日志和步骤说明");

    // 设置代码区域
    ui->codeArea->setLineWrapMode(QTextBrowser::NoWrap);  // 禁用自动换行
    ui->codeArea->setStyleSheet(
        "QTextBrowser {"
        "   font-family: Consolas, monospace;"
        "   font-size: 10pt;"
        "   background-color: #f6f8fa;"  // GitHub风格的背景色
        "   padding: 10px;"
        "}"
    );

    // 为代码区域设置行号区域
    QWidget* viewport = ui->codeArea->viewport();
    viewport->setStyleSheet(
        "background-color: #f6f8fa;"
        "border: none;"
        "line-height: 1.5;"
    );

    // 确保调用setupAlgorithmButtons
    setupAlgorithmButtons();

    // 初始化代码高亮相关变量
    currentHighlightedLine = -1;

    // 初始化变量监视表格
    ui->variableTable->setColumnCount(3);
    ui->variableTable->setHorizontalHeaderLabels({"变量名", "当前值", "说明"});
    ui->variableTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->variableTable->setEditTriggers(QTableWidget::NoEditTriggers);
}

void MainWindow::setupAlgorithmButtons()
{
    QVBoxLayout *layout = new QVBoxLayout(ui->controlGroup);
    QGroupBox *paramGroup = new QGroupBox("参数设置", ui->controlGroup);
    QVBoxLayout *paramLayout = new QVBoxLayout(paramGroup);

    // 添加数据输入区
    QTextEdit *inputArea = new QTextEdit(paramGroup);
    inputArea->setPlaceholderText("输入数据，用逗号分隔");
    inputArea->setMaximumHeight(60);
    paramLayout->addWidget(inputArea);

    // 创建滚动区域
    QScrollArea *scrollArea = new QScrollArea(paramGroup);
    QWidget *buttonsWidget = new QWidget(scrollArea);
    QGridLayout *buttonsLayout = new QGridLayout(buttonsWidget);  // 改用网格布局
    buttonsLayout->setSpacing(5);  // 设置按钮间距

    // 添加算法按钮到滚动区域
    QStringList algorithms = {
        "二叉树遍历", "二叉搜索树", "平衡二叉树",
        "链表操作", "栈操作", "队列操作",
        "图的遍历", "最短路径", "最小生成树"};

    int row = 0, col = 0;
    for (const QString &algo : algorithms)
    {
        QPushButton *btn = new QPushButton(algo, buttonsWidget);
        btn->setMinimumHeight(30);
        btn->setFixedWidth(120);  // 调整宽度适应两列
        algorithmButtons.append(btn);
        buttonsLayout->addWidget(btn, row, col);
        connect(btn, &QPushButton::clicked, this, &MainWindow::onAlgorithmSelected);
        
        col++;
        if (col >= 2) {  // 每行2个按钮
            col = 0;
            row++;
        }
    }
    
    buttonsWidget->setLayout(buttonsLayout);
    scrollArea->setWidget(buttonsWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumHeight(150);
    paramLayout->addWidget(scrollArea);

    layout->addWidget(paramGroup);

    // 添加速度控制滑块
    QSlider *speedSlider = new QSlider(Qt::Horizontal, ui->controlGroup);
    speedSlider->setRange(1, 10);
    speedSlider->setValue(5);
    layout->addWidget(new QLabel("演示速度："));
    layout->addWidget(speedSlider);
}

void MainWindow::onAlgorithmSelected()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (btn)
    {
        QString algorithmName = btn->text();
        currentSelectedAlgorithm = algorithmName;  // 记录当前选中的算法
        QString code = AlgorithmManager::getAlgorithmCode(algorithmName);
        
        // 添加行号并设置代码
        QStringList lines = code.split('\n');
        QString numberedCode;
        for (int i = 0; i < lines.size(); ++i) {
            numberedCode += QString("%1 %2\n")
                .arg(i + 1, 3)  // 行号宽度为3，右对齐
                .arg(lines[i]);
        }
        ui->codeArea->setText(numberedCode);
        ui->codeArea->setFont(QFont("Consolas", 10));
    }
    
    // 重置高亮状态
    currentHighlightedLine = -1;
    codeExecutionSteps.clear();
}

void MainWindow::onCategorySelected()
{
    QToolButton *btn = qobject_cast<QToolButton *>(sender());
    if (btn)
    {
        QString category = btn->text();
        updateAlgorithmButtons(category);
    }
}

void MainWindow::updateAlgorithmButtons(const QString &category)
{
    currentSelectedAlgorithm.clear();  // 清除当前选择的算法
    // 清除现有按钮和布局
    qDeleteAll(algorithmButtons);
    algorithmButtons.clear();

    // 获取现有布局
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->controlGroup->layout());
    
    // 如果存在旧布局，删除它
    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
        delete layout;
    }

    // 创建新布局
    layout = new QVBoxLayout(ui->controlGroup);

    // 创建新的分组框
    QGroupBox *paramGroup = new QGroupBox(category + "演示", ui->controlGroup);
    QVBoxLayout *paramLayout = new QVBoxLayout(paramGroup);

    // 添加数据输入区
    QTextEdit *inputArea = new QTextEdit(paramGroup);
    inputArea->setPlaceholderText("请输入测试数据，用逗号分隔");
    inputArea->setMaximumHeight(60);
    paramLayout->addWidget(inputArea);

    // 创建滚动区域
    QScrollArea *scrollArea = new QScrollArea(paramGroup);
    QWidget *buttonsWidget = new QWidget(scrollArea);
    QGridLayout *buttonsLayout = new QGridLayout(buttonsWidget);  // 改用网格布局
    buttonsLayout->setSpacing(5);  // 设置按钮间距

    // 获取选中分类的算法列表
    QStringList algorithms;
    for (const auto &pair : algorithmCategories) {
        if (pair.first == category) {
            algorithms = pair.second;
            break;
        }
    }

    // 添加算法按钮
    int row = 0, col = 0;
    for (const QString &algo : algorithms)
    {
        QPushButton *btn = new QPushButton(algo, paramGroup);
        btn->setMinimumHeight(30);
        btn->setFixedWidth(120);  // 调整宽度适应两列
        algorithmButtons.append(btn);
        buttonsLayout->addWidget(btn, row, col);
        connect(btn, &QPushButton::clicked, this, &MainWindow::onAlgorithmSelected);
        
        col++;
        if (col >= 2) {  // 每行2个按钮
            col = 0;
            row++;
        }
    }

    buttonsWidget->setLayout(buttonsLayout);
    scrollArea->setWidget(buttonsWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumHeight(150);
    paramLayout->addWidget(scrollArea);

    layout->addWidget(paramGroup);

    // 添加速度控制滑块
    QSlider *speedSlider = new QSlider(Qt::Horizontal, ui->controlGroup);
    speedSlider->setRange(1, 10);
    speedSlider->setValue(5);
    layout->addWidget(new QLabel("演示速度："));
    layout->addWidget(speedSlider);
}

void MainWindow::initScene()
{
    scene->clear();  // 清除场景
    scene->setSceneRect(-200, -200, 400, 400);  // 设置场景大小
    
    // 添加网格背景（可选）
    QPen pen(Qt::lightGray);
    for(int i = -200; i <= 200; i += 20) {
        scene->addLine(i, -200, i, 200, pen);
        scene->addLine(-200, i, 200, i, pen);
    }
}

void MainWindow::highlightCodeLine(int lineNumber)
{
    QTextCursor cursor(ui->codeArea->document());
    QTextCharFormat format;
    
    // 清除之前的高亮
    if (currentHighlightedLine != -1) {
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, currentHighlightedLine);
        cursor.select(QTextCursor::LineUnderCursor);
        format.setBackground(Qt::transparent);
        cursor.mergeCharFormat(format);
    }
    
    // 设置新的高亮
    if (lineNumber >= 0) {
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber);
        cursor.select(QTextCursor::LineUnderCursor);
        format.setBackground(QColor(255, 255, 0, 100)); // 淡黄色背景
        cursor.mergeCharFormat(format);
    }
    
    currentHighlightedLine = lineNumber;
}

QString MainWindow::loadAlgorithmFile(const QString& algorithmName) {
    QString fileName = algorithmName.toLower().remove(" ");
    QString filePath = QApplication::applicationDirPath() + "/algorithms/" + fileName + ".cpp";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    return file.readAll();
}

void MainWindow::onStartClicked()
{
    QTextEdit* inputArea = ui->controlGroup->findChild<QTextEdit*>();
    if (!inputArea) return;
    
    // 检查是否选择了算法
    if (currentSelectedAlgorithm.isEmpty()) {
        StateInfoLable->setText("请先选择一个算法！");
        return;
    }

    // 如果输入为空，生成随机数据
    QString input = inputArea->toPlainText();
    QVector<int> data;
    
    if (input.isEmpty()) {
        // 生成10个随机数
        srand(time(0));
        for(int i = 0; i < 10; i++) {
            data.append(rand() % 100);
        }
        
        // 显示生成的数据
        QString randomData;
        for(int i = 0; i < data.size(); i++) {
            if(i > 0) randomData += ", ";
            randomData += QString::number(data[i]);
        }
        inputArea->setText(randomData);
    } else {
        // 使用输入的数据
        QStringList inputList = input.split(",", Qt::SkipEmptyParts);
        for (const QString& num : inputList) {
            bool ok;
            int value = num.trimmed().toInt(&ok);
            if (!ok) {
                StateInfoLable->setText("输入数据格式错误！");
                return;
            }
            data.append(value);
        }
    }
    
    // 执行算法
    executeAlgorithm(currentSelectedAlgorithm, data);
}

void MainWindow::onNextStepClicked()
{
    if (algorithmSteps.isEmpty() || currentStepIndex >= algorithmSteps.size() - 1) {
        return;
    }
    
    // 执行下一步
    currentStepIndex++;
    
    // 更新代码高亮
    highlightCodeLine(algorithmSteps[currentStepIndex].first - 1);
    
    // 获取当前步骤的信息并直接输出到日志区
    QString stepInfo = algorithmSteps[currentStepIndex].second;
    ui->logArea->append(stepInfo);
    
    // 更新变量表格
    updateVariableTable(algorithmSteps[currentStepIndex].first);
}

// 添加新方法：更新变量表格
void MainWindow::updateVariableTable(int lineNumber)
{
    ui->variableTable->setRowCount(0);  // 清空表格
    
    // 获取当前步骤的信息
    const auto& step = algorithmSteps[currentStepIndex];
    QString stepInfo = step.second;
    
    // 解析变量信息
    QStringList lines = stepInfo.split('\n');
    for (const QString& line : lines) {
        if (line.startsWith("变量：")) {
            QString varInfo = line.mid(3);  // 去掉"变量："前缀
            QStringList vars = varInfo.split(',');
            for (const QString& var : vars) {
                QStringList parts = var.trimmed().split('=');
                if (parts.size() == 2) {
                    int row = ui->variableTable->rowCount();
                    ui->variableTable->insertRow(row);
                    ui->variableTable->setItem(row, 0, new QTableWidgetItem(parts[0]));
                    ui->variableTable->setItem(row, 1, new QTableWidgetItem(parts[1]));
                    
                    // 添加变量说明
                    QString desc;
                    if (parts[0] == "i") desc = "外层循环索引";
                    else if (parts[0] == "j") desc = "内层循环索引";
                    else if (parts[0] == "key") desc = "当前待插入元素";
                    else if (parts[0] == "n") desc = "数组长度";
                    ui->variableTable->setItem(row, 2, new QTableWidgetItem(desc));
                }
            }
            break;  // 只处理第一个变量行
        }
    }
}

void MainWindow::executeAlgorithm(const QString& algorithmName, const QVector<int>& data)
{
    // 获取算法步骤
    QString input;
    for (int i = 0; i < data.size(); ++i) {
        if (i > 0) input += ",";
        input += QString::number(data[i]);
    }
    
    algorithmSteps = AlgorithmManager::getAlgorithmSteps(algorithmName, input);
    currentStepIndex = -1;
    
    // 重置显示
    ui->logArea->clear();
    
    // 只执行第一步
    if (!algorithmSteps.isEmpty()) {
        onNextStepClicked();
    }
}

