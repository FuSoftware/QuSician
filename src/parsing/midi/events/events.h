#ifndef EVENTS_H
#define EVENTS_H

#include "midievent.h"

#include "./channelvoiceevents/channelpressure.h"
#include "./channelvoiceevents/controlchange.h"
#include "./channelvoiceevents/noteoff.h"
#include "./channelvoiceevents/noteon.h"
#include "./channelvoiceevents/pitchwheelchange.h"
#include "./channelvoiceevents/polyphonickeypressure.h"
#include "./channelvoiceevents/programchange.h"

#include "./metaevents/endoftrack.h"
#include "./metaevents/midichannelprefix.h"
#include "./metaevents/sequencenumber.h"
#include "./metaevents/settempo.h"
#include "./metaevents/smpteoffset.h"
#include "./metaevents/textevent.h"
#include "./metaevents/timesignature.h"

#endif // EVENTS_H
