//
// ---------- header ----------------------------------------------------------
//
// project       infinit
//
// license       infinit (c)
//
// file          /home/mycure/infinit/etoile/core/Reference.cc
//
// created       julien quintard   [tue feb 17 12:39:45 2009]
// updated       julien quintard   [wed mar  3 16:17:25 2010]
//

//
// ---------- includes --------------------------------------------------------
//

#include <etoile/core/Reference.hh>

namespace etoile
{
  namespace core
  {

//
// ---------- methods ---------------------------------------------------------
//

    // XXX

    ///
    /// XXX
    ///
    Status		Reference::Size(Offset&			size) const
    {
      enter();

      // set the size.
      size = this->target.length();

      leave();
    }

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this function dumps an block object.
    ///
    Status		Reference::Dump(Natural32		margin) const
    {
      enter();

      // XXX

      leave();
    }

//
// ---------- archivable ------------------------------------------------------
//

    ///
    /// this method serializes the block object.
    ///
    Status		Reference::Serialize(Archive&		archive) const
    {
      enter();

      // XXX

      leave();
    }

    ///
    /// this method extracts the block object.
    ///
    Status		Reference::Extract(Archive&		archive)
    {
      enter();

      // XXX

      leave();
    }

  }
}
