#include <QString>
#include <QStringList>

#include "zealsearchquery.h"

ZealSearchQuery::ZealSearchQuery(const QString &rawQuery)
{
    this->rawQuery = rawQuery;
}


// Returns the docset filter for the given query.
//
// Examples:
//   "android:setTypeFa" #=> "android"
//   "noprefix"          #=> ""
//   ":find"             #=> ""
QString ZealSearchQuery::getDocsetFilter()
{
    if(rawQuery.indexOf(ZealSearchQuery::DOCSET_FILTER_SEPARATOR) >= 1) {
        QString prefix = rawQuery.split(ZealSearchQuery::DOCSET_FILTER_SEPARATOR)[0];
        return prefix.trimmed();
    }

    return "";
}

// Returns the core query, sanitized for use in SQL queries
QString ZealSearchQuery::getSanitizedQuery()
{
    QString q = getCoreQuery();
    q.replace("\\", "\\\\");
    q.replace("_", "\\_");
    q.replace("%", "\\%");
    q.replace("'", "''");
    return q;
}

// Returns the query with any docset prefixes removed.
//
// Examples:
//   "android:setTypeFa" #=> "setTypeFa"
//   "plain"             #=> "plain"
//   ":find"             #=> ":find"
QString ZealSearchQuery::getCoreQuery()
{
    QString docsetPrefix = getDocsetFilter();
    int prefixLen = docsetPrefix.size() + 1; // Remove separator
    if(prefixLen == 1) prefixLen = 0; // No docset prefix - do not remove anything
    return rawQuery.right(rawQuery.size() - prefixLen).trimmed();
}
