// A Simple Thread-safe logger with color coding & output to file options.
#ifndef MINILOGGER_H
#define MINILOGGER_H

#include <cstdio>
#include <ctime>
#include <mutex>
#include <stdarg.h>

namespace MiniEngine
{
    class MiniLogger
    {
    public:
        MiniLogger();
        MiniLogger(const MiniLogger&) = delete;
        MiniLogger& operator=(const MiniLogger&) = delete;
        ~MiniLogger();

        /// @brief Priority of the Logger, if the current priority is info, 
        /// then all messages with the priority of Info & Above will be displayed.
        enum Priority
        {
            TracePriority, DebugPriority, InfoPriority, WarnPriority, ErrorPriority
        };

        /// @brief Set The Priority to the given value.
        /// @param priority: new priority
        void SetPriority(Priority priority) { m_Priority = priority; }

        /// @brief Returns the Current Priority.
        const Priority GetPriority() const { return m_Priority; }

        // By setting this to the given string, this string will be printed every line after the time stamp and message priority.
        void SetInitialString(const char* initialString) { m_InitialString = initialString; }

        const char* GetInitialString() const { return m_InitialString; }

        // Enable file output
        // Logs will be written to /log.txt
        // If the file doesn't exist, it will create it automatically
        // File will be closed when program stops
        // Returns true if a file was successfully opened, false otherwise

        /// @brief If Called & Successfull, then the logs are written to ./log.txt
        /// @return Returns true if file was successfully opened.
        bool OutputToFile()
        {
            m_FilePath = "log.txt";
            return EnableFileOutput();
        }

        // Enable file output
        // Logs will be written to /filepath, provided the filepath is valid
        // If the file doesn't exist, it will create it automatically
        // File will be closed when program stops
        // Returns true if a file was successfully opened, false otherwise
        bool OutputToFile(const char* filepath)
        {
            m_FilePath = filepath;
            return EnableFileOutput();
        }

        // If Output To File was called and no filename was specified, then it will return "log.txt" which is in the working directory.
        const char* GetFilePath() const { return m_FilePath; }

        // Format follows <ctime> strftime format specification
        void SetTimestampFormat(const char* timestamp_format) { m_TimestampFormat = timestamp_format; }

        // Format follows <ctime> strftime format specification
        const char* GetTimestampFormat() const { return m_TimestampFormat; }

        // Log a message (format + optional args, follow printf specification)
        // with log priority level MiniLogger::Trace
        template<typename... Args>
        void Trace(const char* message, Args&& ... args)
        {
            Log(TracePriority, message, args...);
        }

        // Log a message (format + optional args, follow printf specification)
        // with log priority level MiniLogger::Debug
        template<typename... Args>
        void Debug(const char* message, Args&& ... args)
        {
            Log(DebugPriority, message, args...);
        }

        // Log a message (format + optional args, follow printf specification)
        // with log priority level MiniLogger::Info
        template<typename... Args>
        void Info(const char* message, Args&& ... args)
        {
            Log(InfoPriority, message, args...);
        }

        // Log a message (format + optional args, follow printf specification)
        // with log priority level MiniLogger::Warn
        template<typename... Args>
        void Warn(const char* message, Args&& ... args)
        {
            Log(WarnPriority, message, args...);
        }

        // Log a message (format + optional args, follow printf specification)
        // with log priority level MiniLogger::Error
        template<typename... Args>
        void Error(const char* message, Args&& ... args)
        {
            Log(ErrorPriority, message, args...);
        }

    private:
        void FreeFile();
        bool EnableFileOutput();

        const char* MessagePriorityToString(Priority messagePriority);

        void SetColor(Priority messagePriority);

        void Log(Priority messagePriority, const char* message, ...)
        {
            if (m_Priority <= messagePriority)
            {
                std::time_t currentTime = std::time(0);
                std::tm* timestamp = std::localtime(&currentTime);

                std::scoped_lock lock(m_LogLock);

                SetColor(messagePriority);
                std::strftime(m_TimeBuffer, 80, m_TimestampFormat, timestamp);
                std::printf("%s ", m_TimeBuffer);

                const char* messagePriorityString = MessagePriorityToString(messagePriority);
                std::printf(messagePriorityString, "%s");
                std::printf(m_InitialString, "%s");
                va_list arglist;
                va_start(arglist, message);
                std::vprintf(message, arglist);
                va_end(arglist);
                std::printf("\n");

                std::printf("%s", NormalColorCode);

                if (m_File)
                {
                    std::fprintf(m_File, "%s ", m_TimeBuffer);
                    std::fprintf(m_File, "%s", messagePriorityString);
                    std::fprintf(m_File, "%s", m_InitialString);
                    va_start(arglist, message);
                    std::vfprintf(m_File, message, arglist);
                    va_end(arglist);
                    std::fprintf(m_File, "\n");
                }
            }
        }

    private:
        Priority m_Priority;
        std::mutex m_LogLock;
        const char* m_InitialString;
        char m_TimeBuffer[80];
        const char* m_TimestampFormat;
        const char* m_FilePath;
        FILE* m_File;

        static const char* NormalColorCode;
        static const char* WhiteColorCode;
        static const char* GreenColorCode;
        static const char* YellowColorCode;
        static const char* RedColorCode;

    };
}

#endif // !MINILOGGER_H