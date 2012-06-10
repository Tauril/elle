#ifndef  ELLE_CONCEPT_UNIQUABLE_HXX
# define ELLE_CONCEPT_UNIQUABLE_HXX

# include <elle/idiom/Close.hh>

# include <sstream>

# include <elle/concept/Uniquable.hh>
# include <elle/log.hh>
# include <elle/serialize/Base64Archive.hh>
# include <elle/standalone/Log.hh>
# include <elle/standalone/Report.hh>

# include <elle/idiom/Open.hh>

namespace elle
{
  namespace concept
  {

    template<__ECU_ARCHIVE_TPL(Archive)>
      Status Uniquable<Archive>::Save(elle::io::Unique& out) const
      {
        std::ostringstream ss;
        ELLE_LOG_TRACE_COMPONENT("elle.concept");
        try
          {
            ELLE_LOG_TRACE(
                "Save %p of type %s to a Unique string",
                this, ELLE_PRETTY_OBJECT_TYPE(this)
            ) { this->serialize(ss); }
          }
        catch (std::exception const& err)
          {
            escape("%s", err.what());
          }

        out = ss.str();
        return Status::Ok;
      }

      template<__ECU_ARCHIVE_TPL(Archive)>
      Status Uniquable<Archive>::Restore(elle::io::Unique const& in)
      {
        std::istringstream ss(in);
        try
          {
            ELLE_LOG_TRACE_COMPONENT("elle.concept");
            ELLE_LOG_TRACE(
                "Load %p of type %s from a Unique string",
                this, ELLE_PRETTY_OBJECT_TYPE(this)
            ) { this->deserialize(ss); }
          }
        catch (std::exception const& err)
          {
            escape("%s", err.what());
          }

        return Status::Ok;
      }

  }
}

# include <elle/idiom/Close.hh>

#endif

