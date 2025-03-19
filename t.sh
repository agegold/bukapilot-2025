while true; do
    temp=$(awk '{printf "%.1f", $1/1000}' /sys/class/thermal/$(ls /sys/class/thermal/ | grep thermal_zone | sort -V | tail -1)/temp)
    read -r _ u n s i _ < /proc/stat
    sleep 2
    read -r _ u2 n2 s2 i2 _ < /proc/stat
    usage=$(awk -v u=$u -v n=$n -v s=$s -v i=$i -v u2=$u2 -v n2=$n2 -v s2=$s2 -v i2=$i2 'BEGIN {printf "%.2f", (100 * ((u2 + n2 + s2) - (u + n + s)) / ((u2 + n2 + s2 + i2) - (u + n + s + i)))}')
    ram=$(awk '/MemTotal/ {total=$2} /MemAvailable/ {avail=$2} END {printf "%.2f", 100 * (1 - avail / total)}' /proc/meminfo)
    clear
    printf "CPU Temp: %.1f°C | CPU Usage: %.2f%% | RAM Usage: %.2f%%\n\n\n\n\n" "$temp" "$usage" "$ram"
done

