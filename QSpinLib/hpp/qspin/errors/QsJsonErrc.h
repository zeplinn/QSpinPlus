#ifndef QSJSONERROR_H
#define QSJSONERROR_H
#include <system_error>
enum class QsJsonErrc{
    InvalidJsonFormat=1,
    invalidConfigNameFormat,
    invalidVerifyModeFormat,
    InvalidFairnesFormat,
    InvalidConfigFormat,
    InvalidSearchByFormat,
    InvalidSearchDepthFormat,
    InvalidHashValueFormat,
    InvalidMemoryComressionFormat,
    invalidLtlFormat,
    InvalidUseLocalVarFormat,
    InvalidValueFormat,
    DuplicateConfigName,
    InvalidPromelaFilePath,

};
namespace std{
template<>
struct is_error_code_enum<QsJsonErrc> : true_type{};
}
std::error_code make_error_code(QsJsonErrc);
#endif // QSJSONERROR_H
