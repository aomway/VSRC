#!/bin/sh

#uci set wireless.radio0.channel=161
#uci commit wireless
#wifi up

#sleep 1

pre_channels="40 36 44 48 149 153 157 161 165"
pre_count=0

#for pre_channel in $pre_channels
#do
#        echo $pre_channel
#        pre_count=`expr $pre_count + 1`
#done
#echo $pre_count

channels=`iw dev wlan0 scan | grep "primary channel" | awk '{print $4}'`

count=0

for channel in $channels                                                
do                                                                      
        echo $channel                                                   
        count=`expr $count + 1`                                         
done                                                                    
echo $count                                                             
                                                                        
flag=0                                                                  
for pre_channel in $pre_channels              
do                                                                      
        for channel in $channels                                        
        do                                                              
                if [ $pre_channel != $channel ]; then                   
                        flag=`expr $flag + 1`                           
                fi                                                      
        done                                                            
                                                                        
        if [ $flag -eq $count ]; then                                   
                uci set wireless.radio0.channel=$pre_channel            
                uci commit wireless                         
                wifi up                                     
                break                                       
        fi 
        flag=0                                              
done
