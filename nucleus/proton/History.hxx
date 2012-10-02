#ifndef  NUCLEUS_PROTON_HISTORY_HXX
# define NUCLEUS_PROTON_HISTORY_HXX


# include <elle/serialize/VectorSerializer.hxx>
# include <nucleus/proton/Revision.hh>

ELLE_SERIALIZE_SIMPLE(nucleus::proton::History,
                      archive,
                      value,
                      version)
{
  enforce(version == 0);

  archive & value._container;
}

#endif
