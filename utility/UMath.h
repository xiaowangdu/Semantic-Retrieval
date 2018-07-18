#pragma once
#include <QtGlobal>
#include <QDebug>
#include <QAction>
#include <QMenu>


template <typename T> struct TypeChecker;
template <> struct TypeChecker<int> { typedef QVector<int> Type; };
template <> struct TypeChecker<float> { typedef QVector<float> Type; };
template <> struct TypeChecker<qreal> { typedef QVector<qreal> Type; };

template <typename T>
typename TypeChecker<T>::Type &
MaxArray(QVector<QVector<T>>& vc){
	Q_ASSERT(vc.size() > 0);
	QVector<T> res = vc[0];

	for (int i = 1; i < vc.size(); i++) {
		res = MaxVector(res, vc[i]);
	}

	return res;
}

template <typename T>
typename TypeChecker<T>::Type &
MinArray(QVector<QVector<T>>& vc) {
	Q_ASSERT(vc.size() > 0);
	QVector<T> res = vc[0];

	for (int i = 1; i < vc.size(); i++) {
		res = MinVector(res, vc[i]);
	}

	return res;
}

template <typename T>
const typename TypeChecker<T>::Type &
MaxVector(const QVector<T> &p1, const QVector<T> &p2) {
	int size1 = p1.size();
	int size2 = p2.size();
	Q_ASSERT(size1 > 0 && size2 > 0 && size2 == size1);

	for (int i = 0; i < size1; i++) {
		if (p1[i] == p2[i]) {
			continue;
		}
		else {
			return p1[i] > p2[i]? p1: p2;
		}
	}

	return p1;
}

template <typename T>
const typename TypeChecker<T>::Type &
MinVector(const QVector<T> &p1, const QVector<T> &p2) {
	int size1 = p1.size();
	int size2 = p2.size();
	Q_ASSERT(size1 > 0 && size2 > 0 && size2 == size1);

	for (int i = 0; i < size1; i++) {
		if (p1[i] == p2[i]) {
			continue;
		}
		else {
			return p1[i] < p2[i] ? p1 : p2;
		}
	}

	return p1;
}



