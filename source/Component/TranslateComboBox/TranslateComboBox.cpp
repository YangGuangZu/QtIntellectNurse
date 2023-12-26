#include "TranslateComboBox.h"
#include "Manager/AppEnumManager/AppEnumManager.h"

TranslateComboBox::TranslateComboBox(QWidget *parent)
	: QComboBox(parent)
{}

TranslateComboBox::~TranslateComboBox()
{}

void TranslateComboBox::setCurrentText(const QString& text)
{
    QString strInfo = AppEnumManager::Instance().getOriStringByEnumNameAndKey(m_strEnumName, text);
    __super::setCurrentText(strInfo.isEmpty() ? text : strInfo);
}

void TranslateComboBox::setItems(const QString& strEnumName, const QStringList& strlstValue)
{
    clear();
    QStringList strList = AppEnumManager::Instance().getItemsByEnumName(strEnumName, strlstValue);
    addItems(strList.isEmpty() ? strlstValue : strList);

    m_strlstValue.clear();
    m_strlstValue.squeeze();
    m_strEnumName = strEnumName;
    m_strlstValue = strlstValue;
}

QString TranslateComboBox::currentText() const
{
    if (currentIndex() < m_strlstValue.size())
    {
        return m_strlstValue[currentIndex()];
    }
    else
    {
        return __super::currentText();
    }
}
