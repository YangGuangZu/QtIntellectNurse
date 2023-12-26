#include <QImage>
#include <QPixmap>
#include <QEventLoop>
#include <QtConcurrent>
#include <QElapsedTimer>
#include <QStorageInfo>

#include "CommonTool.h"
#define FLOAT_INTER_VALUE 0.0000001

#pragma region 基础功能接口
///
/// \brief 判断文件夹是否存在，不存在则创建
/// \param fullPath
/// \return
///
bool CBaseTool::DirExist(QString fullPath)
{
	QDir dir(fullPath);
	if (dir.exists())
	{
		//存在当前文件夹
		return true;
	}
	else
	{
		//不存在则创建
		bool ok = dir.mkdir(fullPath); //只创建一级子目录，即必须保证上级目录存在
		return ok;
	}
}

///
/// \brief 判断文件夹是否存在，不存在则创建, 可创建多级目录
/// \param fullPath
/// \return
///
bool CBaseTool::DirExistEx(QString fullPath)
{
	QDir dir(fullPath);
	if (dir.exists())
	{
		return true;
	}
	else
	{
		//不存在当前目录，创建，可创建多级目录
		bool ok = dir.mkpath(fullPath);
		return ok;
	}
}

void CBaseTool::saveText2File(const QString& filename, const QString& content)
{
	QFile file(filename);

	file.open(QIODevice::WriteOnly);

	QTextStream stream(&file);

	stream << content;

	stream.flush();

	file.close();
}

QByteArray CBaseTool::readTextFromFile(const QString& filename)
{
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly)) return QByteArray();

	QTextStream stream(&file);
	stream.setEncoding(QStringConverter::Encoding::Utf8); // 设置编码为UTF-8

	QByteArray temp = file.readAll();

	file.close();

	return temp;
}

bool CBaseTool::deleteDirectory(const QString& path)
{
	if (path.isEmpty())
		return false;

	QDir dir(path);
	if (!dir.exists())
		return true;

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
	QFileInfoList fileList = dir.entryInfoList();
	foreach(QFileInfo fi, fileList)
	{
		if (fi.isFile())
			fi.dir().remove(fi.fileName());
		else
			deleteDirectory(fi.absoluteFilePath());
	}
	return dir.rmpath(dir.absolutePath());
}


QStringList CBaseTool::getQMetaEnumStringList(const QMetaEnum& metaEnum)
{
	QStringList strlstTemp;

	strlstTemp.clear();
	for (int iIdx = 0; iIdx < metaEnum.keyCount(); ++iIdx)
	{
		strlstTemp.append(metaEnum.key(iIdx));
	}
	return strlstTemp;
}

#pragma endregion

#pragma region 数据计算
//最近的rect 计算点到四点的距离取最小值
int CBaseTool::minDistancePointToRect(QPoint pos, QRect r)
{
	std::vector<int> calcvalues;
	calcvalues.push_back(abs(pos.x() - r.left()));
	calcvalues.push_back(abs(pos.x() - r.right()));
	calcvalues.push_back(abs(pos.y() - r.top()));
	calcvalues.push_back(abs(pos.y() - r.bottom()));
	std::vector<int>::iterator result = std::min_element(calcvalues.begin(), calcvalues.end());
	return *result;
}

// 获取两个点的距离
qreal CBaseTool::getDistance(const QPointF& p1, const QPointF& p2)
{
	qreal distance = sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) + \
		(p1.y() - p2.y()) * (p1.y() - p2.y()));

	return distance;
}

// 比较两个浮点数是否相等
bool CBaseTool::isEqual(qreal number1, qreal number2)
{
	if (abs(number1 - number2) <= FLOAT_INTER_VALUE)
	{
		return true;
	}

	return false;
}

bool CBaseTool::isContainsPolygon(const QPolygonF& Polygon1, const QPolygonF& Polygon2)
{
	for (const QPointF& point : Polygon2) {
		if (!Polygon1.containsPoint(point, Qt::OddEvenFill)) {
			return false;
		}
	}
	return true;
}

bool CBaseTool::isIntersectsPolygon(const QPolygonF& QPolygon1, const QPolygonF& QPolygon2)
{
	return false;
}

qreal CBaseTool::calcRotateAngle(const QPointF& pCenter, const QPointF& pMoveStart, const QPointF& pMoveEnd)
{
	qreal dA = std::sqrt((pMoveEnd.x() - pMoveStart.x()) * (pMoveEnd.x() - pMoveStart.x()) + (pMoveEnd.y() - pMoveStart.y()) * (pMoveEnd.y() - pMoveStart.y()));
	qreal dB = std::sqrt((pCenter.x() - pMoveStart.x()) * (pCenter.x() - pMoveStart.x()) + (pCenter.y() - pMoveStart.y()) * (pCenter.y() - pMoveStart.y()));
	qreal dC = std::sqrt((pCenter.x() - pMoveEnd.x()) * (pCenter.x() - pMoveEnd.x()) + (pCenter.y() - pMoveEnd.y()) * (pCenter.y() - pMoveEnd.y()));

	qreal dCos = (dC * dC + dB * dB - dA * dA) / (2.0 * dB * dC);
	qreal dRotateAngle = (2 * std::acos(dCos) * 180.0 / std::acos(-1.0));

	qreal dCross = pMoveStart.x() * pMoveEnd.y() - pMoveEnd.x() * pMoveStart.y();

	if (dCross > 0)
		dRotateAngle *= -1;

	return dRotateAngle;
}

#pragma endregion

#pragma region Json数据处理

QJsonObject CBaseTool::readLocalJsonByPath(const QString& path, bool& isOk)
{
	isOk = true;
	QJsonObject obj;
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		isOk = false;
		return obj;
	}

	QJsonParseError error;
	QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), &error);
	//判断文件是否完整
	if (error.error != QJsonParseError::NoError)
	{
		isOk = false;
		//qDebug() << "parseJson:" << error->errorString();
		return obj;
	}
	obj = jdc.object(); //获取对象
	return obj;
}

QPointF CBaseTool::JsonToQPointF(QJsonObject & jsonObj)
{
	QPointF point;
	point.setX(jsonObj.value("x").toDouble());
	point.setX(jsonObj.value("y").toDouble());
	return point;
}

QJsonObject CBaseTool::QPointFToJson(const QPointF& point)
{
	QJsonObject jsonObj;
	jsonObj.insert("x", point.x());
	jsonObj.insert("y", point.y());
	return jsonObj;
}

QPoint CBaseTool::JsonToQPoint(QJsonObject& jsonObj)
{
	QPoint point;
	point.setX(jsonObj.value("x").toDouble());
	point.setX(jsonObj.value("y").toDouble());
	return point;
}

QJsonObject CBaseTool::QPointToJson(const QPoint& point)
{
	QJsonObject jsonObj;
	jsonObj.insert("x", point.x());
	jsonObj.insert("y", point.y());
	return jsonObj;
}

QPolygonF CBaseTool::JsonToQPolygonF(QJsonArray& jsonObj)
{
	QPolygonF polygonF;
	polygonF.clear();
	for (int index = 0; index < jsonObj.size(); index++)
	{
		QJsonObject pointJson = jsonObj.at(index).toObject();
		QPointF point = JsonToQPointF(pointJson);
		polygonF.append(point);
	}
	return polygonF;
}

QJsonArray CBaseTool::QPolygonFToJson(const QPolygonF& polygonF)
{
	QJsonArray jsonObj;
	for (const QPointF& point : polygonF)
	{
		QJsonObject pointJson = QPointFToJson(point);
		
		jsonObj.append(pointJson);
	}
	return jsonObj;
}

QPolygon CBaseTool::JsonToQPolygon(QJsonArray& jsonObj)
{
	QPolygon polygon;
	polygon.clear();
	for (int index = 0; index < jsonObj.size(); index++)
	{
		QJsonObject pointJson = jsonObj.at(index).toObject();
		QPoint point = JsonToQPoint(pointJson);
		polygon.append(point);
	}
	return polygon;
}

QJsonArray CBaseTool::QPolygonToJson(const QPolygon& polygon)
{
	QJsonArray jsonObj;
	for (const QPoint& point : polygon)
	{
		QJsonObject pointJson = QPointFToJson(point);

		jsonObj.append(pointJson);
	}
	return jsonObj;
}
#pragma endregion
