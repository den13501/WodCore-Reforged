/*
* Copyright (C) 2008-2020 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
* Copyright (C) 2021 WodCore Reforged
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <zlib.h>
#include "WorldPacket.h"
#include "World.h"

std::mutex gPacketProfilerMutex;
std::map<uint32, uint32> gPacketProfilerData;

//! Compresses packet in place
void WorldPacket::Compress(z_stream* compressionStream)
{
    uint16 uncompressedOpcode = GetOpcode();
    if (uncompressedOpcode & COMPRESSED_OPCODE_MASK)
    {
        TC_LOG_ERROR("network", "Packet with opcode 0x%04X is already compressed!", uncompressedOpcode);
        return;
    }

    uint16 opcode = Opcodes(uncompressedOpcode | COMPRESSED_OPCODE_MASK);
    uint32 size = wpos();
    uint32 destsize = compressBound(size);

    std::vector<uint8> storage(destsize);

    _compressionStream = compressionStream;
    Compress(static_cast<void*>(&storage[0]), &destsize, static_cast<const void*>(contents()), size);
    if (destsize == 0)
        return;

    clear();
    reserve(destsize + sizeof(uint32));
    *this << uint32(size);
    append(&storage[0], destsize);
    SetOpcode(opcode);

    TC_LOG_INFO("network", "Successfully compressed opcode %u (len %u) to %u (len %u)", uncompressedOpcode, size, opcode, destsize);
}

//! Compresses another packet and stores it in self (source left intact)
void WorldPacket::Compress(z_stream* compressionStream, WorldPacket const* source)
{
    ASSERT(source != this);

    uint16 uncompressedOpcode = source->GetOpcode();
    if (uncompressedOpcode & COMPRESSED_OPCODE_MASK)
    {
        TC_LOG_ERROR("network", "Packet with opcode 0x%04X is already compressed!", uncompressedOpcode);
        return;
    }

    uint16 opcode = Opcodes(uncompressedOpcode | COMPRESSED_OPCODE_MASK);
    uint32 size = source->size();
    uint32 destsize = compressBound(size);

    size_t sizePos = 0;
    resize(destsize + sizeof(uint32));

    _compressionStream = compressionStream;
    Compress(static_cast<void*>(&_storage[0] + sizeof(uint32)), &destsize, static_cast<const void*>(source->contents()), size);
    if (destsize == 0)
        return;

    put<uint32>(sizePos, size);
    resize(destsize + sizeof(uint32));

    SetOpcode(opcode);

    TC_LOG_INFO("network", "Successfully compressed opcode %u (len %u) to %u (len %u)", uncompressedOpcode, size, opcode, destsize);
}

void WorldPacket::Compress(void* dst, uint32 *dst_size, const void* src, int src_size)
{
    _compressionStream->next_out = (Bytef*)dst;
    _compressionStream->avail_out = *dst_size;
    _compressionStream->next_in = (Bytef*)src;
    _compressionStream->avail_in = (uInt)src_size;

    int32 z_res = deflate(_compressionStream, Z_SYNC_FLUSH);
    if (z_res != Z_OK)
    {
        TC_LOG_ERROR("network", "Can't compress packet (zlib: deflate) Error code: %i (%s, msg: %s)", z_res, zError(z_res), _compressionStream->msg);
        *dst_size = 0;
        return;
    }

    if (_compressionStream->avail_in != 0)
    {
        TC_LOG_ERROR("network", "Can't compress packet (zlib: deflate not greedy)");
        *dst_size = 0;
        return;
    }

    *dst_size -= _compressionStream->avail_out;
}

void WorldPacket::OnSend()
{
    if (m_opcode != UNKNOWN_OPCODE && _storage.size() > m_BaseSize)
    {
        gPacketProfilerMutex.lock();
        gPacketProfilerData[m_opcode] = std::max((uint32)_storage.size(), (uint32)gPacketProfilerData[m_opcode]);
        gPacketProfilerMutex.unlock();
    }
}
