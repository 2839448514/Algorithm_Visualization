#include "algorithmanager.h"

QString AlgorithmManager::getAlgorithmCode(const QString& algorithmName)
{
    if (algorithmName == "插入排序") {
        return Algorithm::InsertSort::getCode();
    }
    return "// 该算法代码尚未添加...";
}

QVector<QPair<int, QString>> AlgorithmManager::getAlgorithmSteps(const QString& algorithmName, const QString& input)
{
    QStringList inputList = input.split(",", Qt::SkipEmptyParts);
    QVector<int> data;
    for (const QString& num : inputList) {
        data.append(num.trimmed().toInt());
    }
    
    if (algorithmName == "插入排序") {
        return Algorithm::InsertSort::getSteps(data);
    }
    return QVector<QPair<int, QString>>();
}

