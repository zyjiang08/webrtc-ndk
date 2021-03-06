/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef AUDIO_CODING_MODULE_TYPEDEFS_H
#define AUDIO_CODING_MODULE_TYPEDEFS_H

#include "typedefs.h"

namespace webrtc
{

///////////////////////////////////////////////////////////////////////////
// enum AudioPlayoutMode
// An enumerator for different playout modes.
//
// -voice       : This is the standard mode for VoIP calls. The trade-off
//                between low delay and jitter robustness is optimized
//                for high-quality two-way communication.
//                NetEQs packet loss concealment and signal processing
//                capabilities are fully employed.
// -fax         : The fax mode is optimized for decodability of fax signals
//                rather than for perceived audio quality. When this mode
//                is selected, NetEQ will do as few delay changes as possible,
//                trying to maintain a high and constant delay. Meanwhile,
//                the packet loss concealment efforts are reduced.
//
// -streaming   : In the case of one-way communication such as passive
//                conference participant, a webinar, or a streaming application,
//                this mode can be used to improve the jitter robustness at
//                the cost of increased delay.
//
enum AudioPlayoutMode
{
    voice       = 0,
    fax         = 1,
    streaming   = 2
};


///////////////////////////////////////////////////////////////////////////
// enum ACMSpeechType
// An enumerator for possible labels of a decoded frame.
//
// -normal                     : a normal speech frame. If VAD is enabled on the
//                               incoming stream this label indicate that the
//                               frame is active.
// -PLC                        : a PLC frame. The corresponding packet was lost
//                               and this frame generated by PLC techniques.
// -CNG                        : the frame is comfort noise. This happens if VAD
//                               is enabled at the sender and we have received
//                               SID.
// -PLCCNG                     : PLC will fade to comfort noise if the duration
//                               of PLC is long. This labels such a case.
// -VADPassive                 : the VAD at the receiver recognizes this frame as
//                               passive.
//
enum ACMSpeechType
{
    normal     = 0,
    PLC        = 1,
    CNG        = 2,
    PLCCNG     = 3,
    VADPassive = 4
};


///////////////////////////////////////////////////////////////////////////
// enum ACMVADMode
// An enumerator for aggressiveness of VAD
// -VADNormal                : least aggressive mode.
// -VADLowBitrate            : more aggressive than "VADNormal" to save on
//                             bit-rate.
// -VADAggr                  : an aggressive mode.
// -VADVeryAggr              : the most agressive mode.
//
enum ACMVADMode
{
    VADNormal     = 0,
    VADLowBitrate = 1,
    VADAggr       = 2,
    VADVeryAggr   = 3
};


///////////////////////////////////////////////////////////////////////////
// enum ACMCountries
// An enumerator for countries, used when enabling CPT for a specific country.
//
enum ACMCountries
{
    ACMDisableCountryDetection = -1, // disable CPT detection
    ACMUSA = 0,
    ACMJapan,
    ACMCanada,
    ACMFrance,
    ACMGermany,
    ACMAustria,
    ACMBelgium,
    ACMUK,
    ACMCzech,
    ACMDenmark,
    ACMFinland,
    ACMGreece,
    ACMHungary,
    ACMIceland ,
    ACMIreland,
    ACMItaly,
    ACMLuxembourg,
    ACMMexico,
    ACMNorway,
    ACMPoland,
    ACMPortugal,
    ACMSpain,
    ACMSweden,
    ACMTurkey,
    ACMChina,
    ACMHongkong,
    ACMTaiwan,
    ACMKorea,
    ACMSingapore,
    ACMNonStandard1  // non-standard countries
};

///////////////////////////////////////////////////////////////////////////
// enum ACMAMRPackingFormat
// An enumerator for different bit-packing format of AMR codec according to
// RFC 3267.
//
// -AMRUndefined           : undefined.
// -AMRBandwidthEfficient  : bandwidth-efficient mode.
// -AMROctetAlligned       : Octet-alligned mode.
// -AMRFileStorage         : file-storage mode.
//
enum ACMAMRPackingFormat
{
    AMRUndefined            = -1,
    AMRBandwidthEfficient   = 0,
    AMROctetAlligned        = 1,
    AMRFileStorage          = 2
};


///////////////////////////////////////////////////////////////////////////
//
//   Struct containing network statistics
//
// -currentBufferSize      : current jitter buffer size in ms
// -preferredBufferSize    : preferred (optimal) buffer size in ms
// -currentPacketLossRate  : loss rate (network + late) (in Q14)
// -currentDiscardRate     : late loss rate (in Q14)
// -currentExpandRate      : fraction (of original stream) of synthesized speech
//                           inserted through expansion (in Q14)
// -currentPreemptiveRate  : fraction of synthesized speech inserted through
//                           pre-emptive expansion (in Q14)
// -currentAccelerateRate  : fraction of data removed through acceleration (in Q14)
typedef struct 
{
    WebRtc_UWord16 currentBufferSize;
    WebRtc_UWord16 preferredBufferSize;
    WebRtc_UWord16 currentPacketLossRate;
    WebRtc_UWord16 currentDiscardRate;
    WebRtc_UWord16 currentExpandRate;
    WebRtc_UWord16 currentPreemptiveRate;
    WebRtc_UWord16 currentAccelerateRate;
} ACMNetworkStatistics;

///////////////////////////////////////////////////////////////////////////
//
//   Struct containing jitter statistics
//
// -jbMinSize               : smallest Jitter Buffer size during call in ms
// -jbMaxSize               : largest Jitter Buffer size during call in ms
// -jbAvgSize               : the average JB size, measured over time - ms
// -jbChangeCount           : number of times the Jitter Buffer changed (using Accelerate or Pre-emptive Expand)
// -lateLossMs              : amount (in ms) of audio data received late
// -accelerateMs            : milliseconds removed to reduce jitter buffer size
// -flushedMs               : milliseconds discarded through buffer flushing
// -generatedSilentMs       : milliseconds of generated silence
// -interpolatedVoiceMs     : milliseconds of synthetic audio data (non-background noise)
// -interpolatedSilentMs    : milliseconds of synthetic audio data (background noise level)
// -numExpandTiny           : count of tiny expansions in output audio less than 250 ms*/
// -numExpandSmall          : count of small expansions in output audio 250 to 500 ms*/
// -numExpandMedium         : count of medium expansions in output audio 500 to 2000 ms*/
// -numExpandLong           : count of long expansions in output audio longer than 2000
// -longestExpandDurationMs : duration of longest audio drop-out
// -countIAT500ms           : count of times we got small network outage (inter-arrival time in [500, 1000) ms)
// -countIAT1000ms          : count of times we got medium network outage (inter-arrival time in [1000, 2000) ms)
// -countIAT2000ms          : count of times we got large network outage (inter-arrival time >= 2000 ms)
// -longestIATms            : longest packet inter-arrival time in ms
// -minPacketDelayMs        : min time incoming Packet "waited" to be played
// -maxPacketDelayMs        : max time incoming Packet "waited" to be played
// -avgPacketDelayMs        : avg time incoming Packet "waited" to be played
//
typedef struct 
{
    WebRtc_UWord32 jbMinSize;
    WebRtc_UWord32 jbMaxSize;
    WebRtc_UWord32 jbAvgSize;
    WebRtc_UWord32 jbChangeCount;
    WebRtc_UWord32 lateLossMs;
    WebRtc_UWord32 accelerateMs;
    WebRtc_UWord32 flushedMs;
    WebRtc_UWord32 generatedSilentMs;
    WebRtc_UWord32 interpolatedVoiceMs;
    WebRtc_UWord32 interpolatedSilentMs;
    WebRtc_UWord32 numExpandTiny;
    WebRtc_UWord32 numExpandSmall;
    WebRtc_UWord32 numExpandMedium;
    WebRtc_UWord32 numExpandLong;
    WebRtc_UWord32 longestExpandDurationMs;
    WebRtc_UWord32 countIAT500ms;
    WebRtc_UWord32 countIAT1000ms;
    WebRtc_UWord32 countIAT2000ms;
    WebRtc_UWord32 longestIATms;
    WebRtc_UWord32 minPacketDelayMs;
    WebRtc_UWord32 maxPacketDelayMs;
    WebRtc_UWord32 avgPacketDelayMs;
} ACMJitterStatistics;

///////////////////////////////////////////////////////////////////////////
//
// Enumeration of background noise mode a mapping from NetEQ interface.
//
// -On                  : default "normal" behavior with eternal noise
// -Fade                : noise fades to zero after some time
// -Off                 : background noise is always zero
//
enum ACMBackgroundNoiseMode
{
    On,
    Fade,
    Off
};


} // namespace webrtc

#endif
