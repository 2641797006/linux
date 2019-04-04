--1
drop table if exists `ex1_customer`;
create table `ex1_customer` (
	`customid` varchar(17) default null,
	`name` varchar(10) default null,
	`sex` varchar(2) default null,
	`age` int default null,
	`xfg` decimal(10,2) default null,
	`address` varchar(50) default null,
	`memo` varchar(100) default null
) engine=InnoDB default charset=utf8mb4;

--1(insert)
lock tables `ex1_customer` write;
insert into `ex1_customer` values ('0', '傻逼', '保密', '18', '99.99', '北京', '哇咔咔');
unlock tables;

--1(print)
select * from `ex1_customer`;

