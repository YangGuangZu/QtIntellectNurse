#pragma once

#include <QObject>
#include <QDir>
#include <QMetaEnum>
#include <QProcess>
//Json 处理
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

class CBaseTool : public QObject
{
	Q_OBJECT
public:

	enum class DiskSpaceType
	{
		KiloByte = 0x0,
		MegaByte = 0x1,
		GigaByte = 0x2,
		TeraByte = 0x3,
		DefaultType = 0xFF
	};
	Q_ENUM(DiskSpaceType);

#pragma region 基础功能接口
	///
	/// \brief 判断文件夹是否存在，不存在则创建
	/// \param fullPath
	/// \return
	///
	static bool DirExist(QString fullPath);

	///
	/// \brief 判断文件夹是否存在，不存在则创建, 可创建多级目录
	/// \param fullPath
	/// \return
	///
	static bool DirExistEx(QString fullPath);

	/// <summary>
	/// 保存文字至文件
	/// </summary>
	/// <param name="filename">文件名</param>
	/// <param name="content">内容</param>
	static void saveText2File(const QString& filename, const QString& content);

	/// <summary>
	/// 从文件内读取信息
	/// </summary>
	static QByteArray readTextFromFile(const QString& filename);

	/// <summary>
	/// 删除文件夹 包含其内部的文件
	/// </summary>
	/// <param name="path">路径</param>
	/// <returns></returns>
	static bool deleteDirectory(const QString& path);

	/// <summary>
	/// 根据队列大小获取序号列表
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="lstT"></param>
	/// <returns></returns>
	template<typename T>
	static QStringList getNumberListByList(const QList<T> & lstT);

	/// <summary>
	/// 依据枚举类型获取枚举字符
	/// </summary>
	/// <param name="metaEnum"></param>
	/// <returns></returns>
	static QStringList getQMetaEnumStringList(const QMetaEnum & metaEnum);

	/// <summary>
	/// 保持某个队列长度
	/// 当超过时删除
	/// 当不足时补全
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="lstT"></param>
	/// <param name="desiredSize"></param>
	/// <param name="stT"></param>
	template<typename T>
	static void keepListSize(QList<T>& lstT, int desiredSize, T stT);

	// 获取磁盘剩余容量
	static uint getDiskAvailableStorage(QString strPath, DiskSpaceType eDiskSpaceType = DiskSpaceType::MegaByte);

	// 判断磁盘剩余容量是否满足给定值 单位为GB
	static bool checkDiskAvailableStorageGreaterThan(QString strPath, uint uiStorageThres);

	/// <summary>
	/// 获取哈希值
	/// </summary>
	/// <param name="inputString">输入字符串</param>
	/// <returns></returns>
	static QString generateHashIdByQString(const QString& inputString);

	// 获取多个矩形的最小外接矩形
	template<typename T>
	static T calculateBoundingRect(const QList<T>& rectangles) 
	{
		if (rectangles.isEmpty()) {
			// 如果列表为空，返回一个无效的矩形或者抛出异常，根据你的需求
			return T();
		}

		// 初始化最小外接矩形为第一个矩形
		T boundingRect = rectangles.first();

		// 遍历其他矩形，更新最小外接矩形
		for (const T& rect : rectangles) {
			boundingRect = boundingRect.united(rect);
		}

		return boundingRect;
	};

	//水平分割框体
	template<typename T>
	static void splitRectHorizontal(const T& originalRect, T& upperRect, T& lowerRect) {
		qreal midY = originalRect.y() + originalRect.height() / 2.0;

		upperRect = T(originalRect.x(), originalRect.y(), originalRect.width(), midY - originalRect.y());
		lowerRect = T(originalRect.x(), midY, originalRect.width(), originalRect.bottom() - midY);
	}

	//垂直分割框体
	template<typename T>
	static void splitRectVertical(const T& originalRect, T& leftRect, T& rightRect) {
		qreal midX = originalRect.x() + originalRect.width() / 2.0;

		leftRect = T(originalRect.x(), originalRect.y(), midX - originalRect.x(), originalRect.height());
		rightRect = T(midX, originalRect.y(), originalRect.right() - midX, originalRect.height());
	}
#pragma endregion

#pragma region 数据计算
	/// <summary>
	/// 最近的rect 计算点到四点的距离取最小值
	/// </summary>
	/// <param name="pos">点位</param>
	/// <param name="r">矩形</param>
	/// <returns></returns>
	static int minDistancePointToRect(QPoint pos, QRect r);

	/// <summary>
	/// 获取两个点的距离
	/// </summary>
	/// <param name="p1">点1</param>
	/// <param name="p2">点2</param>
	/// <returns>距离</returns>
	static qreal getDistance(const QPointF& p1, const QPointF& p2);

	/// <summary>
	/// 比较两个浮点数是否相等
	/// </summary>
	/// <param name="number1"></param>
	/// <param name="number2"></param>
	/// <returns></returns>
	static bool isEqual(qreal number1, qreal number2);

	/// <summary>
	/// 判断是否包含另一个多边形
	/// </summary>
	/// <param name="QPolygon1"></param>
	/// <param name="QPolygon2"></param>
	/// <returns></returns>
	static bool isContainsPolygon(const QPolygonF & Polygon1, const QPolygonF& Polygon2);

	/// <summary>
	/// 判断是否相交另一个多边形
	/// </summary>
	/// <param name="QPolygon1"></param>
	/// <param name="QPolygon2"></param>
	/// <returns></returns>
	static bool isIntersectsPolygon(const QPolygonF & QPolygon1, const QPolygonF& QPolygon2);

	/// <summary>
	/// 计算角度
	/// </summary>
	/// <param name="pCenter">中心点</param>
	/// <param name="pMoveStart">起始点</param>
	/// <param name="pMoveEnd">末点</param>
	/// <returns>角度</returns>
	static qreal calcRotateAngle(const QPointF& pCenter, const QPointF& pMoveStart, const QPointF& pMoveEnd);
#pragma endregion

#pragma region Json数据处理
	/// <summary>
	/// 异步睡眠线程
	/// 在当前线程等待
	/// </summary>
	/// <param name="timeout">毫秒级</param>
	/// <returns></returns>
	static bool asynSleep(qint64 timeout);
#pragma endregion

#pragma region Json数据处理
	//json 文件读取
	static QJsonObject readLocalJsonByPath(const QString & path, bool & isOk);
	//json Point读取与存储
	static QPointF JsonToQPointF(QJsonObject & jsonObj);
	static QJsonObject QPointFToJson(const QPointF& point);

	static QPoint JsonToQPoint(QJsonObject& jsonObj);
	static QJsonObject QPointToJson(const QPoint& point);
	//json QPolygon 读取与存储
	static QPolygonF JsonToQPolygonF(QJsonArray& jsonObj);
	static QJsonArray QPolygonFToJson(const QPolygonF& polygonF);

	static QPolygon JsonToQPolygon(QJsonArray& jsonObj);
	static QJsonArray QPolygonToJson(const QPolygon& polygon);
#pragma endregion

#pragma region QList处理相关
	/// <summary>
	/// 两组队列比较 移除两组相公有的对象 防止误删
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="listOri"></param>
	/// <param name="listTag"></param>
	template <typename T>
	static void sievingListCollection(QList<T>& listOri, QList<T>& listTag)
	{
		for (const T& obj : listOri)
		{
			if (listTag.contains(obj))
			{
				listOri.removeOne(obj);
			}
		}

		qDeleteAll(listOri);
		listOri.clear();

		listOri = listTag;
	}

	/// <summary>
	/// 两组队列比较 保留两组相公有的对象 防止误删
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="listOri"></param>
	/// <param name="listTag"></param>
	template <typename T>
	static void saveSameListCollection(QList<T>& listOri, QList<T>& listTag)
	{
		for (const T& obj : listOri)
		{
			if (listTag.contains(obj))
			{
				listOri.removeOne(obj);
			}
		}

		qDeleteAll(listOri);
		listOri.clear();

		listOri = listTag;
	}
#pragma endregion
private:
};

template<typename T>
inline QStringList CBaseTool::getNumberListByList(const QList<T>& lstT)
{
	QStringList lstNumber;
	for (int i = 0; i < lstT.size(); i++)
	{
		lstNumber.append(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0')));
	}
	return lstNumber;
}

template<typename T>
inline void CBaseTool::keepListSize(QList<T>& lstT, int desiredSize, T stT)
{
	while (lstT.size() > desiredSize) {
		lstT.removeLast();
	}

	while (lstT.size() < desiredSize) {
		lstT.append(stT);
	}
}
