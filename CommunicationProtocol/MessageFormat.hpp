#pragma once

namespace
{

extern constexpr const char SeqIdStr[] = "SeqId:";
extern constexpr const char MsgTypeStr[] = "MsgType:";
extern constexpr const char SequenceStr[] = "Sequence:";
extern constexpr const char PayloadLenghtStr[] = "PayloadLength:";
extern constexpr const char PayloadStr[] = "PAYLOAD:";

}  // namespace

template <const char* part, const char*... chars>
constexpr std::size_t calculateSize()
{
    std::size_t size =+ strlen(part) + 5;
    if constexpr (sizeof...(chars) > 0)
    {
        size += calculateSize<chars...>();
    }
    return size;
}

template <const char*... chars>
struct FormatSizeBuilder
{
    static constexpr std::size_t size = calculateSize<chars...>();
};

template <const char*... chars>
struct MessageFormat
{
    using SizeBuilder = FormatSizeBuilder<chars...>;
    char str[SizeBuilder::size];
};

constexpr int constexpr_strcpy(char* dest, const char* src)
{
    int n = 0;
    while((*(dest++) = *(src++))){ n++; }
    return n;
}

template <const char* part, const char*... chars>
constexpr void fill(char* table, int cursor, int index)
{
    std::size_t size =+ strlen(part);
    constexpr_strcpy(table + cursor, part);
    cursor += size;
    table[cursor++] = ' ';
    table[cursor++] = '%';
    table[cursor++] = '0' + index;
    table[cursor++] = '%';
    table[cursor++] = ' ';
    if constexpr (sizeof...(chars) > 0)
    {
        fill<chars...>(table, cursor, ++index);
    }
    else
    {
        table[--cursor] = '\0';
    }
}

template <const char*... chars>
constexpr MessageFormat<chars...> build()
{
    MessageFormat<chars...>  format;
    fill<chars...> (format.str, 0, 1);

    return format;
}

namespace
{

using SimpleMessageFormat = MessageFormat<SeqIdStr, MsgTypeStr, PayloadLenghtStr, PayloadStr>;
using SequenceMessageFormat = MessageFormat<SeqIdStr, MsgTypeStr, SequenceStr, PayloadLenghtStr, PayloadStr>;

constexpr SimpleMessageFormat simpleMessageFormat = build<SeqIdStr, MsgTypeStr, PayloadLenghtStr, PayloadStr>();
constexpr SequenceMessageFormat sequenceMessageFormat = build<SeqIdStr, MsgTypeStr, SequenceStr, PayloadLenghtStr, PayloadStr>();

}  // namespace
