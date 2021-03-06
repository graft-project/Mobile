#include "feedmodel.h"

static const QString scFeedPubDate("ddd, dd MMM yyyy hh:mm:ss +0000");
static const QString scFormattedDate("MMMM dd, yyyy");

FeedModel::FeedModel(QObject *parent) : QAbstractListModel(parent)
{
}

FeedModel::~FeedModel()
{
    qDeleteAll(mFeeds);
}

QVariant FeedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= mFeeds.count())
    {
        return QVariant();
    }

    FeedItem *feed = mFeeds.at(index.row());
    Q_ASSERT(feed);
    switch (role)
    {
    case FormattedDateRole:
        return feed->mPubDate.toString(scFormattedDate);
    case FullFeedPathRole:
        return feed->mFullFeedPath;
    case TimeStampRole:
        return feed->mPubDate.toSecsSinceEpoch();
    case DescriptionRole:
        return feed->mDescription;
    case PubDateRole:
        return feed->mPubDate.toString(scFeedPubDate);
    case ContentRole:
        return feed->mContent;
    case TitleRole:
        return feed->mTitle;
    case ImageRole:
        return feed->mImage;
    case LinkRole:
        return feed->mLink;
    case IDRole:
        return feed->mID;
    default:
        return QVariant();
    }
}

int FeedModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mFeeds.count();
}

bool FeedModel::isLinkExists(const QString &link) const
{
    const auto it = std::find_if(mFeeds.constBegin(), mFeeds.constEnd(),
                                       [&link](FeedItem *feedItem)
    {
        return feedItem && feedItem->mLink == link;
    });
    return it != mFeeds.constEnd();
}

bool FeedModel::updateData(const FeedModel::FeedItem &feed, int index)
{
    FeedModel::FeedItem *item = itemAt(index);
    if (item)
    {
        item->mFullFeedPath = feed.mFullFeedPath;
        item->mDescription = feed.mDescription;
        item->mPubDate = feed.mPubDate;
        item->mContent = feed.mContent;
        item->mTitle = feed.mTitle;
        item->mImage = feed.mImage;
        item->mLink = feed.mLink;
        item->mID = feed.mID;

        QModelIndex modelIndex = this->index(index);
        emit dataChanged(modelIndex, modelIndex);
        return true;
    }
    return false;
}

FeedModel::FeedItem *FeedModel::itemAt(int index) const
{
    if (index >= 0 && index < mFeeds.count())
    {
        return mFeeds.at(index);
    }
    return nullptr;
}

void FeedModel::add(FeedModel::FeedItem *feed)
{
    if (feed && !isLinkExists(feed->mLink))
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mFeeds.append(feed);
        endInsertRows();
    }
}

QHash<int, QByteArray> FeedModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FormattedDateRole] = "formattedDate";
    roles[FullFeedPathRole] = "fullFeedPath";
    roles[DescriptionRole] = "description";
    roles[TimeStampRole] = "timeStamp";
    roles[PubDateRole] = "pubDate";
    roles[ContentRole] = "content";
    roles[TitleRole] = "title";
    roles[ImageRole] = "image";
    roles[LinkRole] = "link";
    roles[IDRole] = "id";
    return roles;
}
