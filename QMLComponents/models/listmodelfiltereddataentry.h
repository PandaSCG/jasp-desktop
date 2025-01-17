//
// Copyright (C) 2013-2018 University of Amsterdam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.
//


#ifndef LISTMODELFILTEREDDATAENTRY_H
#define LISTMODELFILTEREDDATAENTRY_H

#include "listmodeltableviewbase.h"

class Filter;
class ListModelFilteredDataEntry : public ListModelTableViewBase
{
	Q_OBJECT
	Q_PROPERTY(QString	filter		READ filter		WRITE setFilter		NOTIFY filterChanged	)
	Q_PROPERTY(QString	colName		READ colName	WRITE setColName	NOTIFY colNameChanged	)
	Q_PROPERTY(QString	extraCol	READ extraCol	WRITE setExtraCol	NOTIFY extraColChanged	)

public:
	explicit ListModelFilteredDataEntry(TableViewBase * parent);
	~ListModelFilteredDataEntry();

	QVariant					data(	const QModelIndex &index, int role = Qt::DisplayRole)	const	override;
	Qt::ItemFlags				flags(	const QModelIndex &index)								const	override;
	void						filterDoneHandler(const QString & name, const QString & error)			override;
	const QString		&		filter()														const				{ return _tableTerms.filter;	}
	const std::string	&		filterName()													const				{ return _filterName;			}
	const QString		&		colName()														const				{ return _tableTerms.colName;	}
	const QString				extraCol()														const				{ return _tableTerms.extraCol;	}
	const sizetvec		&		filteredRowToData()												const				{ return _filteredRowToData;	}
	const QStringList	&		dataColumns()													const				{ return _dataColumns;			}
	void						initTableTerms(const TableTerms& terms)									override;
	int							getMaximumColumnWidthInCharacters(size_t columnIndex)			const	override;
	bool						isEditable(const QModelIndex& index)							const	override	{ return index.column() >= columnCount(); }
	void						itemChanged(int column, int row, QVariant value, QString type)			override;

	void						refreshModel()															override;

	bool						areColumnNamesVariables()										const	override	{ return true; }
	void						informDataSetOfInitialValues();

public slots:
	void						sourceTermsReset()															override;
	void						initialValuesChanged()														override;
	void						setFilter(	QString filter);
	void						setColName(	QString colName);
	void						setExtraCol(QString extraCol);

signals:
	void						filterChanged(	QString filter);
	void						colNameChanged(	QString colName);
	void						extraColChanged(QString extraCol);
	void						acceptedRowsChanged();

private slots:
	void						dataSetChangedHandler();
	void						runFilter();

private:
	void						setAcceptedRows(boolvec newRows);
	size_t						getDataSetRowCount()	const;
	void						fillTable();

	
private:
	boolvec						_acceptedRows;
	sizetvec					_filteredRowToData;
	std::map<size_t, double>	_enteredValues;
	doublevec					_initialValues;
	int							_editableColumn = 0;
	QStringList					_dataColumns,
								_extraColsStr;
	std::string					_filterName;
	Filter					*	_filter			= nullptr;
	bool						_informOnce		= false;
};

#endif // LISTMODELFILTEREDDATAENTRY_H
