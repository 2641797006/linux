-- 5 (1)
select `SNAME`,`CITY` from `S`;

-- 5 (2)
select `PNAME`,`COLOR`,`WEIGHT` from `P`;

-- 5 (3)
select distinct `JNO` from `SPJ` where `SNO`='S1' order by `JNO`;

-- 5 (4) *****
select `PNO`,`JNO` from `SPJ` order by `JNO`,`PNO`;

-- 5 (5)
select distinct `PNO` from `SPJ`,`S` where `CITY`='上海' and `SPJ`.`SNO`=`S`.`SNO` order by `PNO`;

-- 5 (6)
select distinct `JNO` from `SPJ`
	where `SNO` in (
	select distinct `SNO` from `S`
		where `CITY`='上海'
	) order by `JNO`;

-- 5 (7)
select distinct `JNO` from `SPJ`
	where `JNO` not in (
	select distinct `JNO` from `SPJ`,`S`
		where `CITY`='天津' and `SPJ`.`SNO`=`S`.`SNO`
	) order by `JNO`;

-- 5 (8)
update `P` set `COLOR`='蓝' where `COLOR`='红';
select * from `P`;

-- 5 (9)
select * from `SPJ` where `JNO`='J4' and `PNO`='P6';
update `SPJ` set `SNO`='S3' where `SNO`='S5' and `JNO`='J4' and `PNO`='P6';
select * from `SPJ` where `JNO`='J4' and `PNO`='P6';

-- 5 (10)
select * from `S`;
delete from `S` where `SNO`='S2';
select * from `S`;

select * from `SPJ`;
delete from `SPJ` where `SNO`='S2';
select * from `SPJ`;

-- 5 (11)
select * from `SPJ`;

lock tables `SPJ` write;
insert into `SPJ` values ('S2', 'J6', 'P4', 200);
unlock tables;

select * from `SPJ`;

