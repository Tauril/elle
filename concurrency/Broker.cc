//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// author        julien quintard   [sun may 29 14:29:01 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <reactor/thread.hh>

#include <elle/concurrency/Broker.hh>
#include <elle/concurrency/Callback.hh>
#include <elle/concurrency/Closure.hh>
#include <elle/concurrency/Program.hh>

namespace elle
{
  namespace concurrency
  {

//
// ---------- constructors & destructors --------------------------------------
//

#if defined(INFINIT_LINUX) || defined(INFINIT_MACOSX)
    ///
    /// default constructor.
    ///
    Broker::Broker(const Natural16                              descriptor):
      descriptor(descriptor),
      notifier(descriptor, ::QSocketNotifier::Read)
    {
    }
#elif defined(INFINIT_WINDOWS)
    ///
    /// default constructor.
    ///
    Broker::Broker(HANDLE                                       hEvent):
      notifier(hEvent)
    {
    }
#else
# error "unsupported platform"
#endif

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method activates the broker.
    ///
    Status              Broker::Activate()
    {
#if defined(INFINIT_LINUX) || defined(INFINIT_MACOSX)
      // connect the QT signals.
      if (this->connect(&this->notifier, SIGNAL(activated(int)),
                        this, SLOT(_trigger())) == false)
        escape("unable to connect the signal");
#elif defined(INFINIT_WINDOWS)
      // connect the QT signals.
      if (this->connect(&this->notifier, SIGNAL(activated(HANDLE)),
                        this, SLOT(_trigger())) == false)
        escape("unable to connect the signal");
#else
# error "unsupported platform"
#endif

      return StatusOk;
    }

    ///
    /// this method deactivates the broker.
    ///
    Status              Broker::Deactivate()
    {
#if defined(INFINIT_LINUX) || defined(INFINIT_MACOSX)
      // disconnect the QT signals.
      if (this->disconnect(&this->notifier, SIGNAL(activated(int)),
                           this, SLOT(_trigger())) == false)
        escape("unable to disconnect from the signal");
#elif defined(INFINIT_WINDOWS)
      // disconnect the QT signals.
      if (this->disconnect(&this->notifier, SIGNAL(activated(HANDLE)),
                           this, SLOT(_trigger())) == false)
        escape("unable to disconnect from the signal");
#else
# error "unsupported platform"
#endif

      return StatusOk;
    }

//
// ---------- callbacks -------------------------------------------------------
//

    ///
    /// this callback is triggered in a new fiber so that it can
    /// wait for events or resources.
    ///
    Status              Broker::Trigger()
    {
#if defined(INFINIT_LINUX) || defined(INFINIT_MACOSX)
      // Q_EMIT the signal.
      if (this->signal.ready.Emit(this->descriptor) == StatusError)
        escape("unable to Q_EMIT the signal");
#elif defined(INFINIT_WINDOWS)
      // Q_EMIT the signal.
      if (this->signal.ready.Emit(this->notifier.handle()) == StatusError)
        escape("unable to Q_EMIT the signal");
#else
# error "unsupported platform"
#endif

      return StatusOk;
    }

//
// ---------- slots -----------------------------------------------------------
//

    ///
    /// this slot is launched whenever data is present on the file descriptor.
    ///
    /// the callback is therefored triggered.
    ///
    void                Broker::_trigger()
    {
#if defined(INFINIT_LINUX) || defined(INFINIT_MACOSX)
      //
      // the following part should not be necessary but it turns out
      // that QT triggers this event even though there is nothing to
      // be read on the socket.
      //
      // \todo XXX check in future versions to be sure that this bug
      //           diseppear: launching Infinit and trying CTRL^C does
      //           not work without this code.
      //           note that this does not even work on MacOS X in
      //           which select succeeds but the FUker later blocks,
      //           probably because there is not enough data to
      //           complete a FUSE header.
      //           this platform-specific code should be moved to
      //           the appropriate FUkers, especially if the number
      //           of such cases (in which the function returns because
      //           of insufficient data to be processed) are low so
      //           that the creation of fibers does not impact the
      //           performance.
      {
        struct timeval  timeout = { 0, 0 };
        ::fd_set        set;

        FD_ZERO(&set);

        FD_SET(this->descriptor, &set);

        int res = ::select(FD_SETSIZE, &set, NULL, NULL, &timeout);
        if (res == 0)
          {
            return;
          }
        else if (res < 0)
          {
            log("select() error: %s", strerror(errno));
            return;
          }
      }
#endif

      new reactor::Thread(scheduler(), "broker trigger",
                          boost::bind(&Broker::Trigger, this), true);
    }
  }
}
