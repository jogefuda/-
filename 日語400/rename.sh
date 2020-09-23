PWD=$(pwd)

function load_filename {
    asd=$(tail -n +2 "$1" | sed -rn 's/^[0-9]+\.//g; p')
    echo ${asd}
}

for i in {1..20}
do
    echo
    echo ====================
    readarray -t NEWFILENAMES <<< $(tail -n +2 "$PWD/$i")
    DIR="$PWD/disc$i"
    if [[ ! -e "$DIR" ]]; then
        echo skip "$DIR" because folder not exist.
        continue
    fi

    echo currently working on "$DIR".
    for file in {00..19}
    do
        OLDFILENAME="$DIR/$file.mp4"
        NEWFILENAME="$DIR/${NEWFILENAMES[${file#0}]}.mp4"
        if [[ -e "$OLDFILENAME" ]]; then
            echo rename $OLDFILENAME to $NEWFILENAME
            mv "${OLDFILENAME}" "${NEWFILENAME}"
        fi
    done
done
