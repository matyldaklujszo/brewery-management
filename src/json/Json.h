#ifndef BREWERY_MANAGEMENT_JSON_H
#define BREWERY_MANAGEMENT_JSON_H

#include <rapidjson/document.h>
#include <functional>
#include <string>
#include <rapidjson/schema.h>

namespace brewery {

class Json {
public:
    virtual ~Json() = default;

    void setSchema(const std::string&);
    void validate(const rapidjson::Document& doc) const;
    static std::string doc2str(rapidjson::Document& doc);
protected:
    void setMember(rapidjson::Value&, const std::string&, const std::function<void(std::string)>&) const;
    std::unique_ptr<rapidjson::SchemaDocument> schema_;
};
}
#endif //BREWERY_MANAGEMENT_JSON_H
