## auto scan and connect wifi ap

#!/bin/sh


found=0
while [ $found -eq 0 ]
do

count_ssid=0
count_bss=0

iw dev wlan0 scan > /tmp/scan.txt


ssids=`cat /tmp/scan.txt | grep "SSID:" | awk '{print $2}'`
echo $ssids


for ssid in $ssids                                         
do                                                         
        var=${ssid:0:6}                                    
        if [ $var = "AOMWAY" ]; then                       
                found=1                                    
                break                                      
        fi                                                 
        count_ssid=`expr $count_ssid + 1`                  
        found=0                                            
done                                                       
echo $ssid                                                  
echo $found 

if [ $found -eq 1 ]; then                
                                                           
   bssid=`cat /tmp/scan.txt | grep "BSS" | awk '{print $2}'`
                                                            
        for bss in $bssid                                   
        do                                                  
                if [ $count_ssid -eq $count_bss ]; then     
                        bssid_set=${bss:0:17}               
                        break                               
                fi                                          
                count_bss=`expr $count_bss + 1`             
                                                            
        done                                                
                                                            
        echo $bssid_set                                     
fi                                                          
                                                            
done 

if [ $found -eq 1 ]; then                                   
                                                            
        echo "set wireless"                                 
        uci set wireless.@wifi-iface[0].ssid=$ssid          
        uci set wireless.@wifi-iface[0].bssid=$bssid_set    
                                                            
        uci commit wireless                                 
                                                        
        wifi up                                             
                                                            
fi
