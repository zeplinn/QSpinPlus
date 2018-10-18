#include "qspin/errors/QsJsonErrc.h"
namespace  { // anonymous
struct QsJsonErrcCategory: std::error_category{
	const char* name() const noexcept;
	std::string message(int event) const override;
};
const char *QsJsonErrcCategory::name() const noexcept{
	return "json error";
}
std::string QsJsonErrcCategory::message(int event) const{
	switch (static_cast<QsJsonErrc>(event)) {
	case QsJsonErrc::InvalidJsonFormat:
	case QsJsonErrc::invalidConfigNameFormat:
	case QsJsonErrc::invalidVerifyModeFormat:
	case QsJsonErrc::InvalidFairnesFormat:
	case QsJsonErrc::InvalidConfigFormat:
	case QsJsonErrc::InvalidSearchByFormat:
	case QsJsonErrc::InvalidSearchDepthFormat:
	case QsJsonErrc::InvalidHashValueFormat:
	case QsJsonErrc::InvalidMemoryComressionFormat:
	case QsJsonErrc::invalidLtlFormat:
	case QsJsonErrc::DuplicateConfigName:
	case QsJsonErrc::InvalidPromelaFilePath:
	case QsJsonErrc::InvalidUseLocalVarFormat:
	case QsJsonErrc::InvalidValueFormat:
		return "invalid json";
	default: return "unkwon json error";
	}
}
// ensured default initialized QsJsonErrc ( noexcept )
const QsJsonErrcCategory theQsJsonErrcCategory{};
}// end anonymous namespace

// default function to use throw QJsonErrc
std::error_code make_error_code(QsJsonErrc code){
	return {static_cast<int>(code), theQsJsonErrcCategory };
}
