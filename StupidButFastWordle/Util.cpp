#pragma once

using ll = long long;

ll GetByte(ll num, int pos) {
    return (num >> (pos * 8)) & 0xFF;
}