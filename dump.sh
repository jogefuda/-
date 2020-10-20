#!/bin/bash
SUDO=sudo
MOUNTPOINT=/mnt
DEVICE=/dev/sr0



# utils
function to_sec {
    IFS=':' read -r h m s <<<"$1"
    echo "$(echo "($h * 60 + $m) * 60 + $s" | bc)"
}

function wait_until_inject {
    echo -n 'waiting for cd in'
    while true
    do
        $SUDO mount /dev/sr0 /mnt 2>/dev/null
        if [[ $? != 0 ]]; then
            sleep 3
            echo -n .
        else
            break
        fi
    done
}

function unmount_cdrom {
    umount $DEVICE
}

function get_segment_info {
    local info=$(lsdvd -c "$MOUNTPOINT" 2>/dev/null)
    local longest=$(echo "${info}" | awk '/^Longest/{print $3}' )
    local chapter_length=$(lsdvd -c $MOUNTPOINT 2>/dev/null | awk -v longest=$longest '
        BEGIN {
            curr_title = 0
        }

        cf && /^\s*Chapter/ {
            print substr($4, 0, length($4)-1)
        }

        /^Title/ {
            curr_title +=1
            if (curr_title == longest)
                cf = 1
            else
                cf = 0
        }
    ')

    local accu=0
    for time in $chapter_length; do
        local sec=$(to_sec $time)
        accu=$(echo "$accu + $sec" | bc)
        echo -n $accu,
    done
}

get_segment_info
