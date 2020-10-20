#!/bin/sh

longest=3
lsdvd -c /mnt 2>/dev/null | awk -v longest=$longest '
    BEGIN {
        target = 0
    }

	cf && /^\s*Chapter/ {
        print $0
	}

	/^Title/ {
        curr_title +=1
        if (curr_title == longest c)
            cf = 1
        else
            cf = 0
	}

	END {
		print activePort"#"ports;
	}

'
