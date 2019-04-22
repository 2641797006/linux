-- 4 (1)
select distinct `SNO` from `SPJ` where `JNO`='J1';

-- 4 (2)
select `SNO` from `SPJ` where `JNO`='J1' and `PNO`='P1';

-- 4 (3)
select `SNO` from `SPJ`,`P`
	where `SPJ`.`JNO`='J1' and `P`.`COLOR`='红' and `SPJ`.`PNO`=`P`.`PNO`;

-- 4 (4)
select distinct `JNO` from `SPJ` where `JNO` not in (
	select distinct `JNO` from `SPJ`,`S`,`P`
	where `S`.`CITY`='天津' and `SPJ`.`SNO`=`S`.`SNO` and `P`.`COLOR`='红'
	and `SPJ`.`PNO`=`P`.`PNO`
);

-- 4 (5)
/*
select distinct `JNO` from `SPJ` where (
	select distinct `PNO` from `SPJ`
		where `SNO`='S1';
	) in (
	select distinct `PNO` from 
*/



