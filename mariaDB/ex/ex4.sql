--1
drop table if exists `ex4_cc`;
create table `ex4_cc` (
	`Cc1` varchar(20) default null,
	`Cc2` int default null,
	`Cc3` dec(10,2) default null,
	`Cc4` varchar(60) default null
) engine=InnoDB default charset=utf8mb4;

--2
lock tables `ex4_cc` write;
insert into `ex4_cc` values
	('赵一', 20, 580.00, '重邮宿舍12-3-5'),
	('钱二', 19, 540.00, '南福苑5-2-9'),
	('孙三', 21, 555.50, '学生新区21-5-15'),
	('李四', 22, 480.00, '重邮宿舍8-2-22'),
	('周五', 20, 495.50, '学生新区23-4-8'),
	('吴六', 19, 435.00, '南福苑2-5-12');
unlock tables;

--2(print)
select * from `ex4_cc`;

--3
update `ex4_cc` set `Cc3`=`Cc3`+5 where `Cc2`<=20;

--3(print)
select * from `ex4_cc`;

--4
delete from `ex4_cc` where `Cc2`>=20 and `Cc3`>=500;

--4(print)
select * from `ex4_cc`;

