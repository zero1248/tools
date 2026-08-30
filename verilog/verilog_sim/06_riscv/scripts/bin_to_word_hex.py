#!/usr/bin/env python3
"""Convert a little-endian raw RV32 binary to one 32-bit word per hex line."""
import argparse
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("binary", type=Path)
    parser.add_argument("hexfile", type=Path)
    args = parser.parse_args()

    data = args.binary.read_bytes()
    if len(data) % 4:
        data += bytes(4 - len(data) % 4)
    words = [int.from_bytes(data[i:i + 4], "little") for i in range(0, len(data), 4)]
    args.hexfile.write_text("".join(f"{word:08x}\n" for word in words), encoding="ascii")


if __name__ == "__main__":
    main()
