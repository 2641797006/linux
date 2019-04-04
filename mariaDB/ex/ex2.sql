drop table if exists `ex2_student`;

create table `ex2_student` (
	`id` varchar(17) default null,
	`name` varchar(10) default null,
	`sex` varchar(2) default null,
	`age` int default null,
	`score` decimal(6,2) default null
) engine=InnoDB default charset=utf8mb4;

lock tables `ex2_student` write;

insert into `ex2_student` values
	('A0001', '赵一', '男', 20, 580.00),
	('B0002', '钱二', '女', 19, 540.00),
	('C0003', '孙三', '男', 21, 555.50),
	('D0004', '李四', '男', 22, 480.00),
	('E0005', '周五', '女', 20, 495.50),
	('F0006', '吴六', '男', 19, 435.00);

unlock tables;
