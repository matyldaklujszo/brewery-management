#include "Json.h"
#include <iostream>
#include <rapidjson/writer.h>
#include <logging/LogHelpers.h>

using namespace brewery;

void
Json::setMember(rapidjson::Value& doc, const std::string& member,
                           const std::function<void(std::string)>& setter) const
{
    auto itr = doc.FindMember(member.c_str());
    if (itr != doc.MemberEnd() && itr->value.IsString())
    {
        setter(itr->value.GetString());
    }
}

void
Json::setSchema(const std::string& schema)
{
    rapidjson::Document doc;
    if (doc.Parse(schema.c_str()).HasParseError())
    {
        LOG_ERROR("Schema is not a valid json");
        // TODO throw
    }
    schema_ = std::make_unique<rapidjson::SchemaDocument>(doc);
}

void
Json::validate(const rapidjson::Document &doc) const
{
    if (doc.HasParseError())
    {
        LOG_ERROR("Document is not a valid json");
        // TODO throw
    }

    if (!schema_)
    {
        return;
    }

    rapidjson::SchemaValidator validator(*schema_);
    if (!doc.Accept(validator))
    {
        LOG_ERROR("Document is not valid with a schema");
        // TODO throw
    }
}

std::string
Json::doc2str(rapidjson::Document &doc)
{
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    doc.Accept(writer);

    return strbuf.GetString();
}
