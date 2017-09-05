#pragma once

#include <string>

#include <elle/attribute.hh>
#include <elle/Printable.hh>
#include <elle/Buffer.hh>

#include <elle/service/aws/Keys.hh>

namespace elle
{
  namespace service
  {
    namespace aws
    {
      class SigningKey
        : public elle::Printable
      {
        /*-------------.
        | Construction |
        `-------------*/
      public:
        SigningKey(std::string const& aws_secret,
                   RequestTime const& request_time,
                   std::string const& aws_region,
                   Service const& aws_service);

        std::string
        sign_message(std::string const& message);

        ELLE_ATTRIBUTE_R(elle::Buffer, key);

        /*----------.
        | Printable |
        `----------*/
      public:
        void
        print(std::ostream& stream) const override;
      };
    }
  }
}
