set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=true; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=500;

USE queryPlatform;

ADD ARCHIVE python.tar.gz;
ADD FILE libpython2.7.so;
ADD FILE libpython2.7.so.1.0;
ADD FILE libboost_python.so;
ADD FILE libboost_python.so.1.53.0;
ADD FILE libgezi.so;
ADD FILE ./libencoding_convert.so;
ADD FILE ./gezi.py;
ADD FILE ./gezi_common.py;
ADD FILE ./print-info.py;

DROP TABLE IF EXISTS gezi_t;
CREATE TABLE gezi_t AS 
SELECT L.uid, create_time, uname, score, forum_name, title, content, feature
FROM 
(
	SELECT uid, create_time, uname, forum_name, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content
	FROM default.pbdata
	WHERE day = 20150303
)L
JOIN ${hiveconf:itable} R
ON L.uid = R.uid and L.uid = 68540686
DISTRIBUTE BY uid 
SORT BY uid, create_time DESC;

