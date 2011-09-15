//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// author        julien quintard   [mon feb 22 11:21:39 2010]
//

#ifndef ELLE_NETWORK_PACKET_HH
#define ELLE_NETWORK_PACKET_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/package/Archive.hh>

namespace elle
{
  using namespace package;

  namespace network
  {

//
// ---------- types -----------------------------------------------------------
//

    ///
    /// this type represents a message in its network format i.e an archive.
    ///
    typedef Archive		Packet;

  }
}

#endif
