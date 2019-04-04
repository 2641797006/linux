--1
drop table if exists `ex5_Student`;
create table `ex5_Student` (
	`ID` varchar(20) default null,
	`Name` varchar(10) default null,
	`Age` int default null,
	`Department` varchar(30) default null
) engine=InnoDB default charset=utf8mb4;

--2
drop table if exists `ex5_Course`;
create table `ex5_Course` (
	`CourseID` varchar(15) default null,
	`CourseName` varchar(30) default null,
	`CourseBefore` varchar(15) default null
) engine=InnoDB default charset=utf8mb4;

--3
drop table if exists `ex5_Choose`;
create table `ex5_Choose` (
	`ID` varchar(20) default null,
	`CourseID` varchar(30) default null,
	`Score` dec(5,2) default null
) engine=InnoDB default charset=utf8mb4;

--4
lock tables `ex5_Student` write;
insert into `ex5_Student` values
	('00001', '张三', 20, '计算机系'),
	('00002', '李四', 19, '计算机系'),
	('00003', '王五', 21, '计算机系');
unlock tables;

--4(print)
select * from ex5_Student;

--5
lock tables `ex5_Course` write;
insert into `ex5_Course` values
	('C1', '计算机引论', null),
	('C2', 'PASCAL语言', 'C1'),
	('C3', '数据结构', 'C2');
unlock tables;

--5(print)
select * from `ex5_Course`;

--6
lock tables `ex5_Choose` write;
insert into `ex5_Choose` values
	('00001', 'C1', 95),
	('00001', 'C2', 80),
	('00001', 'C3', 84),
	('00002', 'C1', 80),
	('00002', 'C2', 85),
	('00003', 'C1', 78),
	('00003', 'C3', 70);
unlock tables;

--6(print)
select * from `ex5_Choose`;

--7
select `ID`,`Name` from `ex5_Student` where `Department`='计算机系';

--8
select `s`.`ID`, `s`.`Name`, `co`.`CourseName`, `ch`.`Score`
	from `ex5_Student` as `s`, `ex5_Course` as `co`, `ex5_Choose` as `ch`
	where `s`.`ID`=`ch`.`ID` and `ch`.`CourseID`=`co`.`CourseID`;

--9
select @ex5_score := `c`.`Score`
	from `ex5_Student` as `s`, `ex5_Choose` as `c`
	where `s`.`Name`='张三' and `s`.`ID`=`c`.`ID` and `c`.`CourseID`='C1';
select `ID`,`Score` from `ex5_Choose` where `CourseID`='C1' and `Score`<@ex5_score;

--10
select `c1`.`ID`
	from `ex5_Choose` as `c1`, `ex5_Choose` as `c2`
	where `c1`.`ID`=`c2`.`ID` and `c1`.`CourseID`='C2' and `c2`.`CourseID`='C3';
