#include "MiniLogger.h"

namespace MiniEngine
{
    const char* MiniLogger::NormalColorCode = "\x1B[0m";
    const char* MiniLogger::WhiteColorCode = "\x1B[37m";
    const char* MiniLogger::GreenColorCode = "\x1B[32m";
    const char* MiniLogger::YellowColorCode = "\x1B[33m";
    const char* MiniLogger::RedColorCode = "\x1B[31m";

    MiniLogger::MiniLogger() : m_Priority(MiniLogger::Priority::DebugPriority), m_InitialString(""), m_FilePath(nullptr), m_File(nullptr),
        m_TimeBuffer(), m_TimestampFormat("[%T]") {}

    MiniLogger::~MiniLogger() { FreeFile(); }

    void MiniLogger::FreeFile()
    {
        if (m_File)
        {
            std::fclose(m_File);
            m_File = 0;
        }
    }

    bool MiniLogger::EnableFileOutput()
    {
        FreeFile();
        m_File = std::fopen(m_FilePath, "a");

        return m_File != 0;
    }

    const char* MiniLogger::MessagePriorityToString(Priority messagePriority)
    {
        const char* priorityString;

        switch (messagePriority)
        {
        case MiniLogger::TracePriority: priorityString = "[TRACE] "; break;
        case MiniLogger::DebugPriority: priorityString = "[DEBUG] "; break;
        case MiniLogger::InfoPriority:  priorityString = "[INFO]  "; break;
        case MiniLogger::WarnPriority:  priorityString = "[WARN]  "; break;
        case MiniLogger::ErrorPriority: priorityString = "[ERROR] "; break;
        default: priorityString = "[PRIORITY] "; break;
        }

        return priorityString;
    }

    void MiniLogger::SetColor(Priority messagePriority)
    {
        const char* color;
        switch (messagePriority)
        {
        case MiniLogger::TracePriority: color = WhiteColorCode; break;
        case MiniLogger::DebugPriority: color = WhiteColorCode; break;
        case MiniLogger::InfoPriority:  color = GreenColorCode; break;
        case MiniLogger::WarnPriority:  color = YellowColorCode; break;
        case MiniLogger::ErrorPriority: color = RedColorCode; break;
        default: color = NormalColorCode; break;
        }

        std::printf("%s", color);
    }
}