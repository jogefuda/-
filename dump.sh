#!/bin/bash
MOUNTPOINT=/mnt
DEVICE=/dev/sr0
OUT_PATH=$(pwd)

# utils
function to_beauty_time {
    local t=$1
    local m=$(echo "$t / 60" | bc)
    echo "Elapsed: $m minute{s}"
}

to_beauty_time 60

function to_sec {
    IFS=':' read -r h m s <<<"$1"
    echo "$(echo "($h * 60 + $m) * 60 + $s" | bc)"
}

#
function wait_until_inject {
    echo -n 'Waiting for cd '
    while true
    do
        mount /dev/sr0 /mnt 2>/dev/null
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
    eject
}

function concat_vob {
    local info=$(lsdvd -c "$MOUNTPOINT" 2>/dev/null)
    local longest=$(echo "${info}" | awk '/^Longest/{print $3}' )
    local files=$(find "$MOUNTPOINT/VIDEO_TS" -not -path "$MOUNTPOINT/VIDEO_TS" -name "VTS_${longest}_*.VOB" | sort)
    echo "Concating! ${files}"
    echo "This may take copule of minutes."
    # cp -u -v $files /tmp
    cat $files > "$OUT_PATH/concat.VOB"
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
            curr_title += 1
            if (curr_title == longest)
                cf = 1
            else
                cf = 0
        }
    ')

    local accu=0
    local ret=''
    for time in $chapter_length; do
        local sec=$(to_sec $time)
        accu=$(echo "$accu + $sec" | bc)
        ret+=${accu},
    done
    echo ${ret:0:-1}
}

function split_track {
    local segs=$(get_segment_info)
    ffmpeg -i "$OUT_PATH/concat.VOB" -f segments -segment_times "$segs" -map 0:v:0 -map 0:a:0 -c:a copy -c:v copy "%02d.mp4"
}

n=${1-1}
while true
do
    eject
    #wait_until_inject
    time_a=$(date +%s)
    dump_path="$OUT_PATH/disc$n"
    mkdir -p $dump_path
    cd "$dump_path"
    #concat_vob
    split_track
    (( n=n+1 ))
    unmount_cdrom
    time_b=$(date +%s)
    to_beauty_time $(( time_b-time_a ))
done

