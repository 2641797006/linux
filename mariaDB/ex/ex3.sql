--1
drop table if exists `ex3_aa`;
create table `ex3_aa` (
	`Aa1` varchar(20) default null,
	`Aa2` int default null,
	`Aa3` dec(10,2) default null
) engine=InnoDB default charset=utf8mb4;

--1(insert)
lock tables `ex3_aa` write;
insert into `ex3_aa` values ('aa1', 666, 6.66);
unlock tables;

--1(print)
select * from `ex3_aa`;

--2
drop table if exists `ex3_bb`;
create table `ex3_bb` (
	`Bb1` varchar(30) default null,
	`Bb2` int default null,
	`Bb3` dec(6,2) default null
) engine=InnoDB default charset=utf8mb4;

--2(insert)
lock tables `ex3_bb` write;
insert into `ex3_bb` values
	('six', 666, 6.66);
unlock tables;

--2(print)
select * from `ex3_bb`;

--3
drop table `ex3_aa`;

--4
alter table `ex3_bb` add `Bb4` varchar(20) default null;

--4(print)
select * from `ex3_bb`;

--5
drop view if exists `Viewbb`;
create view `Viewbb` (`Viewbb1`, `Viewbb2`)
as
select `Bb1`,`Bb4` from `ex3_bb`;

--5(print)
select * from `Viewbb`;

--6
drop view `Viewbb`;

--7
create index `Indexbb` on `ex3_bb` (`Bb3`);

--7(print)
show index from `ex3_bb`;

--8
drop index `Indexbb` on `ex3_bb`;

