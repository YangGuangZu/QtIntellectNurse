#pragma once

#include <QComboBox>

class TranslateComboBox  : public QComboBox
{
	Q_OBJECT

public:
	TranslateComboBox(QWidget *parent = nullptr);
	~TranslateComboBox();
private:
	QString m_strEnumName;
	QStringList m_strlstValue;

public:
	/// <summary>
	/// 设置对应值
	/// </summary>
	/// <param name="value"></param>
	void setCurrentText(const QString& text);

	/// <summary>
	/// 设置项目队列
	/// </summary>
	/// <param name="items"></param>
	void setItems(const QString& strEnumName, const QStringList& strlstValue);

	/// <summary>
	/// 获取对应值
	/// </summary>
	QString currentText() const;
};
