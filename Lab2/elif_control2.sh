echo -n "Is it morninng? Please answer yes or no: "
read timeofday
if [ "$timeofday" = "yes" ]; then
    echo "Good morning"
elif [ "$timeofday" = "no" ]; then
    echo "Good afternoon"
else
    echo "Sorry, $timeofday not recognized. Emter yes or no"
    exit 1
fi
exit 0
