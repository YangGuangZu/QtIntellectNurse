#include <QLineEdit>
#include "BasicPopupView.h"

BasicPopupView::BasicPopupView(PopupParams& stPopupParams, const QString& title, QWidget* parent /* = nullptr */)
	: QDialog(parent),
	m_stPopupParams(stPopupParams),
	m_stTempPopupParams(stPopupParams)
{
	ui.setupUi(this);
	ui.labelTitle->setText(title);
	init();
}

BasicPopupView::~BasicPopupView()
{}

void BasicPopupView::init()
{
	for (PopupInfoParam & stPopupInfoParam : m_stPopupParams)
	{
		createRowInfo(stPopupInfoParam);
	}
}

void BasicPopupView::createRowInfo(PopupInfoParam& stPopupInfoParam)
{
	QLabel* pLabel = new QLabel(ui.widget);
	QLineEdit* pLineEdit = new QLineEdit(ui.widget);

	pLabel->setText(stPopupInfoParam.title);
	pLineEdit->setText(stPopupInfoParam.content);

	connect(pLineEdit, &QLineEdit::editingFinished, [=, &stPopupInfoParam]() {
		stPopupInfoParam.content = pLineEdit->text();
		}
	);
	ui.formLayout->addRow(pLabel, pLineEdit);
}

void BasicPopupView::on_btnOk_clicked()
{
	close();
}

void BasicPopupView::on_btnChannel_clicked()
{
	m_stPopupParams = m_stTempPopupParams;
	done(1000);
}
