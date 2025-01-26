#ifndef ALGORITHMANAGER_H
#define ALGORITHMANAGER_H

#include <QString>
#include <QVector>
#include <QPair>

namespace Algorithm {
    class InsertSort {
    public:
        static QString getCode();
        static QVector<QPair<int, QString>> getSteps(const QVector<int>& data);
    };
}

class AlgorithmManager {
public:
    static QString getAlgorithmCode(const QString& algorithmName);
    static QVector<QPair<int, QString>> getAlgorithmSteps(const QString& algorithmName, const QString& input);
};

#endif // ALGORITHMANAGER_H
