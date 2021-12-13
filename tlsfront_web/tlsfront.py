import os
import aiohttp, json
from aiohttp import web
import asyncio
import json

_gstats = {}

gstats = {"tlsfront-testrail": {"192.168.114.221": [{"appSessStructNotAvail": 0, "socketBindIpv4": 56, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 54, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 2, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 107, "socketReuseSetFail": 0, "sslAcceptSuccess": 52, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 106, "sslConnInitFail": 1, "sslConnInitInSec": 0, "sslConnInitProgress": 106, "sslConnInitRate": 0, "sslConnInitSuccess": 52, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 53, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 53, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 53, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 53, "tlsfrontThroughput": 0}, {"appSessStructNotAvail": 0, "socketBindIpv4": 56, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 54, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 2, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 107, "socketReuseSetFail": 0, "sslAcceptSuccess": 52, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 106, "sslConnInitFail": 1, "sslConnInitInSec": 0, "sslConnInitProgress": 106, "sslConnInitRate": 0, "sslConnInitSuccess": 52, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 53, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 53, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 53, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 53, "tlsfrontThroughput": 0}, {"appSessStructNotAvail": 0, "socketBindIpv4": 56, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 54, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 2, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 107, "socketReuseSetFail": 0, "sslAcceptSuccess": 52, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 106, "sslConnInitFail": 1, "sslConnInitInSec": 0, "sslConnInitProgress": 106, "sslConnInitRate": 0, "sslConnInitSuccess": 52, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 53, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 53, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 53, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 53, "tlsfrontThroughput": 0}], "192.168.114.220": [{"appSessStructNotAvail": 0, "socketBindIpv4": 31, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 29, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 57, "socketReuseSetFail": 0, "sslAcceptSuccess": 28, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 56, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 56, "sslConnInitRate": 0, "sslConnInitSuccess": 28, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 28, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 28, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 28, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 28, "tlsfrontThroughput": 0}, {"appSessStructNotAvail": 0, "socketBindIpv4": 31, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 29, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 57, "socketReuseSetFail": 0, "sslAcceptSuccess": 28, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 56, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 56, "sslConnInitRate": 0, "sslConnInitSuccess": 28, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 28, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 28, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 28, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 28, "tlsfrontThroughput": 0}, {"appSessStructNotAvail": 0, "socketBindIpv4": 31, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 29, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 57, "socketReuseSetFail": 0, "sslAcceptSuccess": 28, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 56, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 56, "sslConnInitRate": 0, "sslConnInitSuccess": 28, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 28, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 28, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 28, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 28, "tlsfrontThroughput": 0}], "sum": {"appSessStructNotAvail": 0, "socketBindIpv4": 87, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 83, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 2, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 164, "socketReuseSetFail": 0, "sslAcceptSuccess": 80, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 162, "sslConnInitFail": 1, "sslConnInitInSec": 0, "sslConnInitProgress": 162, "sslConnInitRate": 0, "sslConnInitSuccess": 80, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 81, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 81, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 81, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 2, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 81, "tlsfrontThroughput": 0}}, "tlsserver": {"192.168.114.219": [{"appSessStructNotAvail": 0, "socketBindIpv4": 2, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 1, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611716, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 0, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 0, "sslConnInitRate": 0, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611715, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 1, "tcpConnInit": 0, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 0, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsserverBytesInSec": 0, "tlsserverThroughput": 16384000}, {"appSessStructNotAvail": 0, "socketBindIpv4": 2, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 1, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611726, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 0, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 0, "sslConnInitRate": 0, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611725, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 1, "tcpConnInit": 0, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 0, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsserverBytesInSec": 0, "tlsserverThroughput": 16384000}, {"appSessStructNotAvail": 0, "socketBindIpv4": 2, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 1, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611736, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 0, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 0, "sslConnInitRate": 0, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611735, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 1, "tcpConnInit": 0, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 0, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsserverBytesInSec": 0, "tlsserverThroughput": 16384000}], "sum": {"appSessStructNotAvail": 0, "socketBindIpv4": 2, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 1, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611736, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 0, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 0, "sslConnInitRate": 0, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611735, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 1, "tcpConnInit": 0, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 0, "tcpConnInitSuccess": 0, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 0, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsserverBytesInSec": 0, "tlsserverThroughput": 16384000}}, "tlsfront-tlsserver": {"192.168.114.218": [{"appSessStructNotAvail": 0, "socketBindIpv4": 611714, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611712, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 1223423, "socketReuseSetFail": 0, "sslAcceptSuccess": 611711, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 10, "sslConnInit": 611711, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611710, "sslConnInitRate": 10, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611711, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 0, "tcpConnInit": 611711, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611711, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 611711, "tlsfrontThroughput": 32768000}, {"appSessStructNotAvail": 0, "socketBindIpv4": 611724, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611722, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 1223443, "socketReuseSetFail": 0, "sslAcceptSuccess": 611721, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 10, "sslConnInit": 611721, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611720, "sslConnInitRate": 10, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611721, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 0, "tcpConnInit": 611721, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611721, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 611721, "tlsfrontThroughput": 32768000}, {"appSessStructNotAvail": 0, "socketBindIpv4": 611734, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611732, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 1223463, "socketReuseSetFail": 0, "sslAcceptSuccess": 611731, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 10, "sslConnInit": 611731, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611730, "sslConnInitRate": 10, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611731, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 0, "tcpConnInit": 611731, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611731, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 611731, "tlsfrontThroughput": 32768000}], "sum": {"appSessStructNotAvail": 0, "socketBindIpv4": 611734, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611732, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 1223463, "socketReuseSetFail": 0, "sslAcceptSuccess": 611731, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 10, "sslConnInit": 611731, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611730, "sslConnInitRate": 10, "sslConnInitSuccess": 0, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 0, "tcpAcceptFail": 0, "tcpAcceptSuccess": 611731, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 10, "tcpActiveConns": 0, "tcpConnInit": 611731, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611731, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 1, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsfrontActSessions": 0, "tlsfrontBytesInSec": 0, "tlsfrontSessions": 611731, "tlsfrontThroughput": 32768000}}, "tlsclient": {"192.168.114.223": [{"appSessStructNotAvail": 0, "socketBindIpv4": 611715, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611714, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611714, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 611714, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611714, "sslConnInitRate": 10, "sslConnInitSuccess": 611714, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 10, "tcpAcceptFail": 0, "tcpAcceptSuccess": 0, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 611714, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611714, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 0, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsclientBytesInSec": 0, "tlsclientThroughput": 16384000}, {"appSessStructNotAvail": 0, "socketBindIpv4": 611725, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611724, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611724, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 611724, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611724, "sslConnInitRate": 10, "sslConnInitSuccess": 611724, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 10, "tcpAcceptFail": 0, "tcpAcceptSuccess": 0, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 611724, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611724, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 0, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsclientBytesInSec": 0, "tlsclientThroughput": 16384000}, {"appSessStructNotAvail": 0, "socketBindIpv4": 611735, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611734, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611734, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 611734, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611734, "sslConnInitRate": 10, "sslConnInitSuccess": 611734, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 10, "tcpAcceptFail": 0, "tcpAcceptSuccess": 0, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 611734, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611734, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 0, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsclientBytesInSec": 0, "tlsclientThroughput": 16384000}], "sum": {"appSessStructNotAvail": 0, "socketBindIpv4": 611735, "socketBindIpv4Fail": 0, "socketBindIpv6": 0, "socketBindIpv6Fail": 0, "socketConnectEstablishFail": 0, "socketConnectEstablishFail2": 0, "socketCreate": 611734, "socketCreateFail": 0, "socketIpTransparentSet": 0, "socketIpTransparentSetFail": 0, "socketLingerSet": 0, "socketLingerSetFail": 0, "socketListenFail": 0, "socketReuseSet": 611734, "socketReuseSetFail": 0, "sslAcceptSuccess": 0, "sslAcceptSuccessInSec": 0, "sslAcceptSuccessRate": 0, "sslConnInit": 611734, "sslConnInitFail": 0, "sslConnInitInSec": 0, "sslConnInitProgress": 611734, "sslConnInitRate": 10, "sslConnInitSuccess": 611734, "sslConnInitSuccessInSec": 0, "sslConnInitSuccessRate": 10, "tcpAcceptFail": 0, "tcpAcceptSuccess": 0, "tcpAcceptSuccessInSec": 0, "tcpAcceptSuccessRate": 0, "tcpActiveConns": 0, "tcpConnInit": 611734, "tcpConnInitFail": 0, "tcpConnInitFailImmediateEaddrNotAvail": 0, "tcpConnInitFailImmediateOther": 0, "tcpConnInitInSec": 0, "tcpConnInitInUse": 0, "tcpConnInitProgress": 0, "tcpConnInitRate": 10, "tcpConnInitSuccess": 611734, "tcpConnInitSuccessInSec": 0, "tcpConnInitSuccessRate": 10, "tcpConnStructNotAvail": 0, "tcpGetSockNameFail": 0, "tcpInitServerFail": 0, "tcpListenStart": 0, "tcpListenStartFail": 0, "tcpListenStop": 0, "tcpListenStructNotAvail": 0, "tcpLocalPortAssignFail": 0, "tcpPollRegUnregFail": 0, "tcpReadFail": 0, "tcpWriteFail": 0, "tcpWriteReturnsZero": 0, "tlsclientBytesInSec": 0, "tlsclientThroughput": 16384000}}}

stats_ticks = 60

async def index_handle(request):
    return web.FileResponse('public/index.html')

async def api_handle(request):
    # gstats['tlsfront-testrail']['sum']['tcpAcceptSuccess'] = gstats['tlsfront-testrail']['sum']['tcpAcceptSuccess'] + 1
    return web.json_response(gstats)

async def api_get_deployments(request):
    return web.json_response(list(gstats.keys()))

app = web.Application()

app.add_routes([web.static('/build', 'public/build')])
app.add_routes([web.static('/assets', 'public/assets')])

app.add_routes([web.route('get'
                            , '/api/deployments'
                            , api_get_deployments)])

app.add_routes([web.route('*', '/api/{api_path:.*}', api_handle)])
app.add_routes([web.route('get', '/{tail:.*}', index_handle)])

class StatsListener:
    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = data.decode()
        stats = json.loads(message)
        appId = stats['appId']
        podIp = stats['podIp']
        del stats['appId']
        del stats['podIp']

        if not gstats.get(appId):
            gstats[appId] = {}
        if not gstats[appId].get(podIp):
            gstats[appId][podIp] = []

        gstats[appId][podIp].append(stats)
        if len(gstats[appId][podIp]) > stats_ticks:
            gstats[appId][podIp].pop(0)


        if gstats[appId].get('sum'):
            del gstats[appId]['sum']

        last_stats = []
        sum_stats = {}
        for _, v in gstats[appId].items():
            if v:
                last_stats.append(v[len(v)-1])

        if last_stats:
            for k, _ in stats.items():
                sum_stats[k] = 0
                for next_stats in last_stats:
                    sum_stats[k] = sum_stats[k]+next_stats[k]

        gstats[appId]['sum'] = sum_stats

def main ():
    global stats_ticks

    cfg_file = '/configs/config.json'
    with open(cfg_file) as f:
        cfg = json.loads(f.read())

    stats_ticks = cfg['stats_ticks']

    loop = asyncio.get_event_loop()
    runner = aiohttp.web.AppRunner(app)
    loop.run_until_complete(runner.setup())
    site = aiohttp.web.TCPSite(runner
                , host=cfg['webui_ip']
                , port=cfg['webui_port']
                , reuse_port=True)
    loop.run_until_complete(site.start())

    listen = loop.create_datagram_endpoint(StatsListener
                    , local_addr=(cfg['webui_ip']
                                    , cfg['stats_port'])
                    , reuse_port=True)

    loop.run_until_complete(listen)

    loop.run_forever()
    # web.run_app(app, port=8888)

if __name__ == '__main__':
    print ('http://localhost:8888')
    main()

