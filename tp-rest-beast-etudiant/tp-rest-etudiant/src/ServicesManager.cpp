#include "ServicesManager.h"

#include <charconv>
#include <optional>
#include <utility>

void ServicesManager::registerService(std::unique_ptr<AbstractService> service)
{
    // TODO Question 3
    services_.push_back(std::move(service));
}

AbstractService* ServicesManager::findService(std::string_view url) const
{
    // TODO Question 3
    // renvoie l'adresse du service correspondant à l'URL,sinon nullptr
    // un service correspond à l'URL si son motif désigne le premier segment de l'URL
    // les URL /version,/version/suite et /version/23 correspondent, /versions ne correspond pas
    // les méthodes std::string_view::starts_with() et .get() du unique_ptr sont utiles
    for (const auto& service : services_) {
        if (url=="/version" || (url.size()>service->getPattern().size() && url.starts_with(service->getPattern()) && url[service->getPattern().size()]=='/')) {
            return service.get();
        }
    }
    return nullptr;
}

http::status ServicesManager::queryService(std::string& out, const std::string& in,
                                           std::string_view url, http::verb method)
{
    // TODO Questions 1, 3, 4, 5, 7, 9, 11
    
    (void)in;
    AbstractService* service = findService(url);
    if (!service) {
        throw ServiceException(http::status::not_found, "Service not found");
    }

    json::value temp;
    
    switch (method) {
        case http::verb::get:
            service->get(temp, std::nullopt);
            break;
        case http::verb::post:
            throw ServiceException(http::status::not_implemented, "POST not implemented yet");
        case http::verb::patch:
            throw ServiceException(http::status::not_implemented, "PATCH not implemented yet");
        default:
            throw ServiceException(http::status::method_not_allowed, "Method not allowed");
    }
    out=json::serialize(temp);
    return http::status::ok;
}
