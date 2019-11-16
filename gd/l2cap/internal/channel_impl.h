/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "common/bidi_queue.h"
#include "l2cap/cid.h"
#include "l2cap/l2cap_packets.h"

namespace bluetooth {
namespace l2cap {
namespace internal {

/**
 * Common interface for internal channel implementation
 */
class ChannelImpl {
 public:
  virtual ~ChannelImpl() = default;

  /**
   * Return the queue end for upper layer (L2CAP user)
   */
  virtual common::BidiQueueEnd<packet::BasePacketBuilder, packet::PacketView<packet::kLittleEndian>>*
  GetQueueUpEnd() = 0;

  /**
   * Return the queue end for lower layer (segmenter and reassembler)
   */
  virtual common::BidiQueueEnd<packet::PacketView<packet::kLittleEndian>, packet::BasePacketBuilder>*
  GetQueueDownEnd() = 0;

  virtual Cid GetCid() const = 0;

  virtual Cid GetRemoteCid() const = 0;

  /**
   * Return one of the supported channel mode as defined above
   */
  virtual RetransmissionAndFlowControlModeOption GetChannelMode() const = 0;

  /**
   * Invoked by the command signalling manager to update the channel mode. Does NOT apply to fixed channel, OR LE
   * credit-based flow control channel
   */
  virtual void SetChannelMode(RetransmissionAndFlowControlModeOption) = 0;
};

}  // namespace internal
}  // namespace l2cap
}  // namespace bluetooth