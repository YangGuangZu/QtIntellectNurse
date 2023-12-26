#include <QComboBox>
#include <QtConcurrent>
#include "CommunicateConfigView.h"
#include "Communication/CommunicationRtu.h"
#include "Tool/CommonTool/CommonTool.h"
#include "Component/PopupTips/PopupManager.h"
#include "Manager/AppEnumManager/CommonEnum/CommonEnum.h"
#include "Component/TranslateComboBox/TranslateComboBox.h"

CommunicateConfigView::CommunicateConfigView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

CommunicateConfigView::~CommunicateConfigView()
{}

void CommunicateConfigView::init()
{
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自动设置列宽
}

void CommunicateConfigView::on_addBtn_clicked() 
{
	int iRowCount = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(iRowCount);
	QTableWidgetItem* pTableWidgetItem = nullptr;
	//通讯别名
	pTableWidgetItem = new QTableWidgetItem(QStringLiteral("请输入别名"));
	ui.tableWidget->setItem(iRowCount, 0, pTableWidgetItem);
	//ui.tableWidget->setItem(iRowCount, 0, pTableWidgetItem);
	//串口号
	TranslateComboBox* pPortComboBox = new TranslateComboBox();
	pPortComboBox->addItems(CommunicationRtu::getSerialPortInfoStringList());
	ui.tableWidget->setCellWidget(iRowCount, 1, pPortComboBox);
	//数据校验
	TranslateComboBox* pSerialParityComboBox = new TranslateComboBox();
	pSerialParityComboBox->setItems(EnumClass::m_qQSerialPortParity.enumName(), CBaseTool::getQMetaEnumStringList(EnumClass::m_qQSerialPortParity));
	ui.tableWidget->setCellWidget(iRowCount, 2, pSerialParityComboBox);
	//波特率
	TranslateComboBox* pSerialBaudRateComboBox = new TranslateComboBox();
	pSerialBaudRateComboBox->setItems(EnumClass::m_qQSerialPortBaudRate.enumName(), CBaseTool::getQMetaEnumStringList(EnumClass::m_qQSerialPortBaudRate));
	ui.tableWidget->setCellWidget(iRowCount, 3, pSerialBaudRateComboBox);
	//数据位
	TranslateComboBox* pSerialDataBitsComboBox = new TranslateComboBox();
	pSerialDataBitsComboBox->setItems(EnumClass::m_qQSerialPortDataBits.enumName(), CBaseTool::getQMetaEnumStringList(EnumClass::m_qQSerialPortDataBits));
	ui.tableWidget->setCellWidget(iRowCount, 4, pSerialDataBitsComboBox);
	//停止位
	TranslateComboBox* pSerialStopBitsComboBox = new TranslateComboBox();
	pSerialStopBitsComboBox->setItems(EnumClass::m_qQSerialPortStopBits.enumName(), CBaseTool::getQMetaEnumStringList(EnumClass::m_qQSerialPortStopBits));
	ui.tableWidget->setCellWidget(iRowCount, 5, pSerialStopBitsComboBox);
	//状态
	pTableWidgetItem = new QTableWidgetItem(QStringLiteral("离线"));
	ui.tableWidget->setItem(iRowCount, 6, pTableWidgetItem);

}

void CommunicateConfigView::on_deleteBtn_clicked()
{
	int curRow = ui.tableWidget->currentRow();
	if (-1 == curRow)
	{
		PopupManager::Instance().addPopupTip(QStringLiteral("错误"), QStringLiteral("当前没有选中通讯信息栏,无法删除"), QtMsgType::QtFatalMsg);
		return;
	}

	ui.tableWidget->removeRow(curRow);
}

void CommunicateConfigView::on_saveBtn_clicked()
{
}

void CommunicateConfigView::on_updateBtn_clicked()
{
	QEventLoop loop;
	QFutureWatcher<void> watcher;
	connect(&watcher, &QFutureWatcher<void>::finished, &loop, &QEventLoop::quit);
	watcher.setFuture(QtConcurrent::run([&]() {
		//获取所有行数
		int iRowCount = ui.tableWidget->rowCount();
		for (int index = 0; index < iRowCount; index++)
		{
			SerialPortParams stSerialPortParams;
			stSerialPortParams.strDisplayName = ui.tableWidget->item(index, 0)->text();
			
			if (TranslateComboBox * pPortComboBox = dynamic_cast<TranslateComboBox *>(ui.tableWidget->cellWidget(index, 1)))
			{
				stSerialPortParams.strPort = pPortComboBox->currentText();
			}
			
			if (TranslateComboBox * pSerialParityComboBox = dynamic_cast<TranslateComboBox *>(ui.tableWidget->cellWidget(index, 2)))
			{
				stSerialPortParams.eSerialParity = QSerialPort::Parity(EnumClass::m_qQSerialPortParity.keyToValue(pSerialParityComboBox->currentText().toStdString().c_str()));
			}
			
			if (TranslateComboBox * pSerialBaudRateComboBox = dynamic_cast<TranslateComboBox *>(ui.tableWidget->cellWidget(index, 3)))
			{
				stSerialPortParams.eSerialBaudRate = QSerialPort::BaudRate(EnumClass::m_qQSerialPortBaudRate.keyToValue(pSerialBaudRateComboBox->currentText().toStdString().c_str()));
			}
			
			if (TranslateComboBox * pSerialDataBitsComboBox = dynamic_cast<TranslateComboBox *>(ui.tableWidget->cellWidget(index, 4)))
			{
				stSerialPortParams.eSerialDataBits = QSerialPort::DataBits(EnumClass::m_qQSerialPortDataBits.keyToValue(pSerialDataBitsComboBox->currentText().toStdString().c_str()));
			}
			
			if (TranslateComboBox * pSerialStopBitsComboBox = dynamic_cast<TranslateComboBox *>(ui.tableWidget->cellWidget(index, 5)))
			{
				stSerialPortParams.eSerialStopBits = QSerialPort::StopBits(EnumClass::m_qQSerialPortStopBits.keyToValue(pSerialStopBitsComboBox->currentText().toStdString().c_str()));
			}
			CommunicationRtu::Instance().addRtuSerialClientBySerialPort(stSerialPortParams);
		}
		CommunicationRtu::Instance().start();
		})
	);
	loop.exec();
}
