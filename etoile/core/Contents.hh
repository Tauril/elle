//
// ---------- header ----------------------------------------------------------
//
// project       etoile
//
// license       infinit (c)
//
// file          /home/mycure/infinit/etoile/core/Contents.hh
//
// created       julien quintard   [mon aug 10 12:07:15 2009]
// updated       julien quintard   [mon mar  8 23:12:04 2010]
//

#ifndef ETOILE_CORE_CONTENTS_HH
#define ETOILE_CORE_CONTENTS_HH

//
// ---------- includes --------------------------------------------------------
//

#include <etoile/core/ContentHashBlock.hh>
#include <etoile/core/Data.hh>
#include <etoile/core/Catalog.hh>
#include <etoile/core/Reference.hh>

namespace etoile
{
  namespace core
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this classes abstracts the data, catalog or reference by embedding
    /// it since the contents is always encrypted.
    ///
    /// therefore, once a contents is retrieved from the hole, the Extract()
    /// method is called which basically extracts an archive i.e the encrypted
    /// version of the embedded block. Then the Decrypt() method can be called
    /// in order (i) decrypt the embedded archive (ii) extract it (iii) build
    /// the embedded object.
    ///
    template <typename T>
    class Contents:
      public ContentHashBlock
    {
    public:
      //
      // identifier
      //
      static const String	Name;

      //
      // constructors & destructors
      //
      Contents();
      ~Contents();

      //
      // methods
      //
      Status		Create();

      Status		Encrypt(const SecretKey&);
      Status		Decrypt(const SecretKey&);

      //
      // interfaces
      //

      // entity
      embed(Entity, Contents);
      // XXX operator==

      // dumpable
      Status		Dump(const Natural32 = 0) const;

      // archivable
      Status		Serialize(Archive&) const;
      Status		Extract(Archive&);

      //
      // attributes
      //
      T*		content;
      Cipher*		cipher;
    };

  }
}

//
// ---------- templates -------------------------------------------------------
//

#include <etoile/core/Contents.hxx>

#endif
