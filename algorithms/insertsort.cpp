#include <QString>
#include <QVector>
#include <QPair>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "algorithmanager.h"

using namespace std;

namespace Algorithm {
namespace {  // 匿名命名空间用于文件作用域的辅助函数
QString arrayToString(const QVector<int>& arr) {
    QString result;
    for(int i = 0; i < arr.size(); i++) {
        if(i > 0) result += " ";
        result += QString::number(arr[i]);
    }
    return result;
}
}

QString InsertSort::getCode() {
    return R"(void insertSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
})";
}

QVector<QPair<int, QString>> InsertSort::getSteps(const QVector<int>& data) {
    QVector<QPair<int, QString>> steps;
    QVector<int> arr = data;
    int n = arr.size();

    // 初始状态
    steps.append({1, QString("[%1]\n变量：n=%2").arg(arrayToString(data)).arg(n)});

    // 执行插入排序
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        steps.append({2, QString("选择 arr[%1]=%2\n变量：i=%1,key=%2").arg(i).arg(key)});

        bool moved = false;
        while(j >= 0 && arr[j] > key) {
            moved = true;
            arr[j + 1] = arr[j];
            j--;

            steps.append({3, QString("移动 => [%1]\n变量：i=%2,j=%3,key=%4").arg(arrayToString(arr)).arg(i).arg(j).arg(key)});
        }

        arr[j + 1] = key;
        QString status = moved ? QString("插入：") : QString("位置正确：");

        steps.append({4, QString("%1[%2]\n变量：i=%3,j=%4,key=%5").arg(status).arg(arrayToString(arr)).arg(i).arg(j).arg(key)});
    }

    steps.append({5, QString("\n最终结果：[%1]")
                         .arg(arrayToString(arr))});
    return steps;
}
} // namespace Algorithm
