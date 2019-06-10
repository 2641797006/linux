-- 1
drop table if exists ex7_Exam;
create table ex7_Exam (
	id varchar(17) default null,
	name varchar(10) default null,
	sex varchar(2) default null,
	age int default null,
	score numeric(6,2) default null,
	address varchar(50) default null,
	memo varchar(100) default null
) engine=InnoDB default charset=utf8mb4;

-- (1)
-- show create table ex7_Exam\G;

-- 2
lock tables ex7_Exam write;
insert into ex7_Exam values
	('A0001', '赵一', '男', 20, 580.00, '重邮宿舍12-3-5', '学习委员'),
	('B0002', '钱二', '女', 19, 540.00, '南福苑5-2-9', '班长'),
	('C0003', '孙三', '男', 21, 555.50, '学生新区21-5-15', '优秀共青团员'),
	('D0004', '李四', '男', 22, 480.00, '重邮宿舍8-2-22', '暂无相关信息'),
	('E0005', '周五', '女', 20, 495.50, '学生新区23-4-8', '暂无相关信息'),
	('F0006', '吴六', '男', 19, 435.00, '南福苑2-5-12', '暂无相关信息');
unlock tables;

-- (2)
select * from ex7_Exam;

-- 3
create index IndexScore on ex7_Exam(score);

-- (3)
show index from ex7_Exam;

-- 4
drop view if exists ViewExam;
create view ViewExam as
select name as ViewExam1, address as ViewExam2
from ex7_Exam;
