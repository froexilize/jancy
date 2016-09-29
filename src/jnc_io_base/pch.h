#pragma once

#include "jnc_ExtensionLib.h"
#include "jnc_CallSite.h"

#include "axl_io_Serial.h"
#include "axl_io_Socket.h"
#include "axl_io_NetworkAdapter.h"
#include "axl_io_MappedFile.h"
#include "axl_sys_Thread.h"
#include "axl_sys_Event.h"
#include "axl_sys_Time.h"
#include "axl_sl_Construct.h"

#if (_AXL_OS_POSIX)
#	include "axl_io_psx_Pipe.h"
#endif

#if (_AXL_OS_WIN)
#	include "axl_io_win_NamedPipe.h"
#elif (_AXL_OS_POSIX)
#	include "axl_io_psx_Pipe.h"
#endif

using namespace axl;

#if (_AXL_OS_WIN)
#	pragma comment (lib, "setupapi.lib")
#	pragma comment (lib, "iphlpapi.lib")
#	include <winioctl.h>
#elif (_AXL_OS_POSIX)
#	include <ifaddrs.h>
#	include <netdb.h>
#	include <net/if.h>
#	include <netinet/tcp.h>
#endif
