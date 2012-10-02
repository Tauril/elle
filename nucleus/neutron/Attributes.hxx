#ifndef NUCLEUS_NEUTRON_ATTRIBUTES_HXX
# define NUCLEUS_NEUTRON_ATTRIBUTES_HXX


# include <elle/serialize/Serializer.hh>

ELLE_SERIALIZE_SIMPLE(nucleus::neutron::Attributes,
                      archive,
                      value,
                      version)
{
  enforce(version == 0);

  archive & value.range;
}

#endif
