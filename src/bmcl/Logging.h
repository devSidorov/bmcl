/*
 * Copyright (c) 2014 CPB9 team. See the COPYRIGHT file at the top-level directory.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "bmcl/Config.h"

#include <functional>

#ifdef BMCL_HAVE_QT
#include <QTextStream>
#include <QBuffer>
#else
#include <sstream>
#endif

#define BMCL_LOG(level) bmcl::Logger(level)
#define BMCL_DEBUG() BMCL_LOG(bmcl::LogLevel::Debug)
#define BMCL_INFO() BMCL_LOG(bmcl::LogLevel::Info)
#define BMCL_WARNING() BMCL_LOG(bmcl::LogLevel::Warning)
#define BMCL_CRITICAL() BMCL_LOG(bmcl::LogLevel::Critical)

namespace bmcl {

enum class LogLevel {
    None = 0, //
    Panic = 1,
    Critical = 2,
    Warning = 3,
    Info = 4,
    Debug = 5
};

using LogHandler = std::function<void(LogLevel level, const char* msg)>;

BMCL_EXPORT void setLogLevel(LogLevel level);
BMCL_EXPORT LogLevel logLevel();
BMCL_EXPORT void setLogHandler(const LogHandler& handler);
BMCL_EXPORT void setLogHandler(LogHandler&& handler);
BMCL_EXPORT void setDefaulLogHandler();
BMCL_EXPORT void log(LogLevel level, const char* msg);

class BMCL_EXPORT Logger {
public:
    inline Logger(LogLevel level);
    ~Logger();

    template <typename T>
    Logger& operator<<(const T& value);
    Logger& operator<<(const char* value);

private:
    LogLevel _level;
#ifdef BMCL_HAVE_QT
    QTextStream _stream;
    QString _buffer;
#else
    std::ostringstream _stream;
#endif
};

inline Logger::Logger(LogLevel level)
    : _level(level)
#ifdef BMCL_HAVE_QT
    , _stream(&_buffer, QIODevice::WriteOnly)
#endif
{
}

template <typename T>
Logger& Logger::operator<<(const T& value)
{
    if ((int)_level <= (int)bmcl::logLevel()) {
        _stream << value;
    }
    return *this;
}

template<>
BMCL_EXPORT Logger& Logger::operator<<(const std::string& value);
};
