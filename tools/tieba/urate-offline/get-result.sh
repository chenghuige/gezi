sh ./urate2.sh $1 &
sh ./behaviour2.sh $1 &
sh ./pc-behav-old2.sh $1 &
sh ./img2.sh $1 &
sh ./tid2.sh $1 &
sh ./ugrade2.sh $1 &
wait

sh ./merge2.sh $1

hive -f ./predict.hql -hiveconf itable=gezi_urate_behaviour_oldbehav_img_lou_ugrade_feature2 otable=gezi_ubehaviour_predict$1

#hive -f ./print-info.hql -hiveconf date=$1 itable=gezi_ubehaviour_predict$1 otable=gezi_uinfo$1

hive -e 'select uid, score from queryPlatform.gezi_ubehaviour_predict'$1' ORDER BY score DESC' > predict.$1.txt
#hive -e 'select * from queryPlatform.gezi_uinfo'$1' ORDER BY score DESC' > uinfo.$1.txt
