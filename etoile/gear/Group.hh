#ifndef ETOILE_GEAR_GROUP_HH
# define ETOILE_GEAR_GROUP_HH

# include <elle/types.hh>

# include <nucleus/proton/Location.hh>
# include <nucleus/neutron/fwd.hh>

# include <etoile/gear/Context.hh>
# include <etoile/gear/Nature.hh>

# include <etoile/automaton/Group.hh>

# include <etoile/wall/Group.hh>

namespace etoile
{
  namespace gear
  {

    /// XXX
    class Group:
      public Context
    {
    public:
      //
      // constants
      //
      static const Nature                       N = NatureGroup;

      //
      // types
      //
      typedef wall::Group                      W;
      typedef automaton::Group                 A;

      typedef nucleus::neutron::Group::Role Role;

      //
      // constructors & destructors
      //
      Group();

      //
      // interfaces
      //

      // dumpable
      elle::Status      Dump(const elle::Natural32 = 0) const;

      //
      // attributes
      //
      nucleus::proton::Location location;

      std::shared_ptr<nucleus::neutron::Group> group;
      std::shared_ptr<nucleus::neutron::Ensemble> ensemble;

      struct
      {
        nucleus::neutron::Group::Role role;
      } rights;
    };

  }
}

#endif
