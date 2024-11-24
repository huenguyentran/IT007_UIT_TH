count=0
for filename in ../../../OS_LAB2_IMG/*; do
    if [[ "$filename" == *.png ]]; then
        count=$((count + 1))
        mv $filename ../../../PNG/
    fi
done
echo So luong file PNG la $count
exit 0