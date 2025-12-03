#!/usr/bin/env python3

import sys
import os
import tempfile
import hashlib
import urllib.request
from urllib.parse import urlparse

def main():
    if len(sys.argv) != 2:
        print("Usage: python url_checksum.py <URL>", file=sys.stderr)
        sys.exit(1)
    
    url = sys.argv[1]
    
    # Create temp file
    with tempfile.NamedTemporaryFile(delete=False) as tmp_file:
        tmp_path = tmp_file.name
    
    try:
        # Download file
        urllib.request.urlretrieve(url, tmp_path)
        
        # Read file and calculate checksums
        with open(tmp_path, 'rb') as f:
            data = f.read()
        
        file_size = len(data)
        
        # 32-bit summing checksum with wrapping
        checksum = sum(data) & 0xFFFFFFFF
        
        # SHA1 digest
        sha1 = hashlib.sha1(data).hexdigest()
        
        # Output format: size,checksum,sha1
        print(f"{file_size},0x{checksum:08x},{sha1}")
        
    finally:
        # Clean up temp file
        if os.path.exists(tmp_path):
            os.unlink(tmp_path)

if __name__ == "__main__":
    main()