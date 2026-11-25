#include "VersionService.h"

VersionService::VersionService() : AbstractService("/version") {}

http::status VersionService::get(json::value& out, std::optional<int> /*id*/) const
{
    // TODO Question 2
    out=json::value{{"major",1},{"minor",0}};
    return http::status::ok;
}
