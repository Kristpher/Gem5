/**
 * Copyright (c) 2018-2020 Inria
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mem/cache/replacement_policies/lip_rp.hh"

#include <cassert>
#include <memory>

#include "params/LIPRP.hh"
#include "sim/cur_tick.hh"

namespace gem5
{

namespace replacement_policy
{

LIP12::LIP12(const Params &p)
  : Base(p)
{
}
bool comp(ReplaceableEntry* r1,ReplacableEntry*r2{
  return std::static_pointer<LIP12ReplData>(r1->
        replacement_data)->lastTouchTick<std::static_pointer<LIP12ReplData>(r2->
        replacement_data)->lastTouchTick;
  }
void
LRU::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
{
    // Reset last touch timestamp
    std::static_pointer_cast<LIP12ReplData>(
        replacement_data)->lastTouchTick = Tick(0);
}

void
LRU::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    // Update last touch timestamp
    std::static_pointer_cast<LIP12ReplData>(
        replacement_data)->lastTouchTick = curTick();
}

void
LRU::reset(const std::shared_ptr<ReplacementData>& cb) const
{
   std::sort(cb.begin(),cb.end(),comp);
   std::static_pointer_case<LIPReplData>(replacement_data)->lastTouchTick=std::static_pointer_case<LIP12ReplData>(blks[11]->replacementData)->lastTouchTick;
   std::static_pointer_cast<LIP12ReplData>(blks[11]->replacementData)->lastTouchTick--;
}

ReplaceableEntry*
LRU::getVictim(const ReplacementCandidates& candidates) const
{
    // There must be at least one replacement candidate
    assert(candidates.size() > 0);

    // Visit all candidates to find victim
    ReplaceableEntry* victim = candidates[0];
    for (const auto& candidate : candidates) {
        // Update victim entry if necessary
        if (std::static_pointer_cast<LIP12ReplData>(
                    candidate->replacementData)->lastTouchTick <
                std::static_pointer_cast<LIP12ReplData>(
                    victim->replacementData)->lastTouchTick) {
            victim = candidate;
        }
    }

    return victim;
}

std::shared_ptr<ReplacementData>
LRU::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new LIP12ReplData());
}

} // namespace replacement_policy
} // namespace gem5