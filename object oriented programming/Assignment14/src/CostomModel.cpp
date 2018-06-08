#include "include/CostomModel.h"

CostomModel::CostomModel(WatchList& w, QObject* parent): QAbstractTableModel{ parent }, wList{w}
{
}

int CostomModel::rowCount(const QModelIndex&) const
{
    return wList.getList().size();
}

int CostomModel::columnCount(const QModelIndex&) const
{
    return 5;
}

QVariant CostomModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();

    std::vector<Movie> movies = wList.getList();
    Movie m = movies[row];

    if (role == Qt::DisplayRole) {
        switch (col) {
            case 0:
                return QString::fromStdString(m.getTitle());

            case 2:
                return QString::fromStdString(m.getReleaseDate());

            case 3:
                return QString::fromStdString(std::to_string(m.getNumberOfLikes()));

            case 4:
                return QString::fromStdString(m.getLink());

            default:
                break;
        }
    }

    if (role == Qt::DecorationRole) {
        if (col == 1) {
            if (m.getGenre() == "Comedy") {
                QPixmap a("./image/comedy.jpeg");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);

            } else if (m.getGenre() == "Action") {
                QPixmap a("./image/action.png");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);

            } else if (m.getGenre() == "Drama/Comedy") {
                QPixmap a("./image/tommy.jpg");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);

            } else if (m.getGenre() == "Adventure") {
                QPixmap a("./image/adventure.jpeg");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);

            } else if (m.getGenre() == "Drama") {
                QPixmap a("./image/drama.jpg");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);

            } else if (m.getGenre() == "Sci-Fi") {
                QPixmap a("./image/scifi.jpg");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);

            } else if (m.getGenre() == "Crime") {
                QPixmap a("./image/crime.jpg");
                return a.scaled(100, 100, Qt::KeepAspectRatioByExpanding);
            }
        }
    }

    return QVariant{};
}

QVariant CostomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString{"Title"};
                case 1:
                    return QString{"Genre"};
                case 2:
                    return QString{"Release Date"};
                case 3:
                    return QString{"Likes"};
                case 4:
                    return QString{"Link"};
                default:
                    break;
            }
        }
    }

    return QVariant{};
}
