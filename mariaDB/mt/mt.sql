-- table S

drop table if exists `S`;
create table `S` (
	`SNO` varchar(2) default null,
	`SNAME` varchar(16) default null,
	`STATUS` int default null,
	`CITY` varchar(8) default null
) engine=InnoDB default charset=utf8mb4;

lock tables `S` write;
insert into `S` values
	('S1', '精益', 20, '天津'),
	('S2', '盛锡', 10, '北京'),
	('S3', '东方红', 30, '北京'),
	('S4', '丰泰盛', 20, '天津'),
	('S5', '为民', 30, '上海');
unlock tables;

select * from `S`;

-- table P

drop table if exists `P`;
create table `P` (
	`PNO` varchar(2) default null,
	`PNAME` varchar(16) default null,
	`COLOR` varchar(8) default null,
	`WEIGHT` int default null
) engine=InnoDB default charset=utf8mb4;

lock tables `P` write;
insert into `P` values
	('P1', '螺母', '红', 12),
	('P2', '螺栓', '绿', 17),
	('P3', '螺丝刀', '蓝', 14),
	('P4', '螺丝刀', '红', 14),
	('P5', '凸轮', '蓝', 40),
	('P6', '齿轮', '红', 30);
unlock tables;

select * from `P`;

-- table J

drop table if exists `J`;
create table `J` (
	`JNO` varchar(2) default null,
	`JNAME` varchar(16) default null,
	`CITY` varchar(8) default null
) engine=InnoDB default charset=utf8mb4;

lock tables `J` write;
insert into `J` values
	('J1', '三建', '北京'),
	('J2', '一汽', '长春'),
	('J3', '弹簧厂', '天津'),
	('J4', '造船厂', '天津'),
	('J5', '机车厂', '唐山'),
	('J6', '无线电厂', '常州'),
	('J7', '半导体厂', '南京');
unlock tables;

select * from `J`;

-- table SPJ

drop table if exists `SPJ`;
create table `SPJ` (
	`SNO` varchar(2) default null,
	`PNO` varchar(2) default null,
	`JNO` varchar(2) default null,
	`QTY` int default null
) engine=InnoDB default charset=utf8mb4;

lock tables `SPJ` write;
insert into `SPJ` values
	('S1', 'P1', 'J1', 200),
	('S1', 'P1', 'J3', 100),
	('S1', 'P1', 'J4', 700),
	('S1', 'P2', 'J2', 100),
	('S2', 'P3', 'J1', 400),
	('S2', 'P3', 'J2', 200),
	('S2', 'P3', 'J4', 500),
	('S2', 'P3', 'J5', 400),
	('S2', 'P5', 'J1', 400),
	('S2', 'P5', 'J2', 100),
	('S3', 'P1', 'J1', 200),
	('S3', 'P3', 'J1', 200),
	('S4', 'P5', 'J1', 100),
	('S4', 'P6', 'J3', 300),
	('S4', 'P6', 'J4', 200),
	('S5', 'P2', 'J4', 100),
	('S5', 'P3', 'J1', 200),
	('S5', 'P6', 'J2', 200),
	('S5', 'P6', 'J4', 500);
unlock tables;

select * from `SPJ`;

