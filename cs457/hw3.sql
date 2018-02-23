-- question 7
-- single block query 
SELECT lname, salary FROM employee WHERE dno != 5 or bdate < '1960-01-01';

-- join in from clause
SELECT lname, salary FROM employee JOIN department ON dno=dnumber WHERE dname != 'Research' or bdate < '1960-01-01';

-- nested query using in
SELECT lname, salary FROM employee WHERE dno in (SELECT dnumber from employee, department WHERE dname != 'Research') or bdate < '1960-01-01';

-- nested query using <> all
SELECT lname, salary FROM employee WHERE dno <>all (SELECT dnumber from employee, department WHERE dname = 'Research') or bdate < '1960-01-01';

-- correlated nested query using 'not exists'
SELECT lname, salary FROM employee WHERE not exists (SELECT * from department WHERE dno=dnumber and dname = 'Research' and bdate > '1960-01-01');

-- nested query in from clause
SELECT lname, salary FROM (SELECT * FROM employee, department WHERE dno=dnumber and (dname != 'Research' or bdate < '1960-01-01'));


-- question 8
-- part a
SELECT lname, pno, hours FROM (SELECT * FROM employee, works_on, department WHERE ssn=essn and dno=dnumber and dname = 'Administration' and hours < 20) ORDER BY hours;

-- part b
SELECT lname, pno, hours FROM (SELECT * FROM employee left join works_on on ssn=essn left join department on dno=dnumber WHERE (dname = 'Administration' or dname='Headquarters') and (hours < 20 or hours is null)) ORDER BY hours;

-- question 9
-- part a
SELECT ssn FROM employee
MINUS
SELECT ssn FROM employee,project,works_on WHERE pname='Computerization' and pnumber=pno and essn=ssn;

-- part b
SELECT ssn FROM employee,project,works_on WHERE pname!='Computerization' and pnumber=pno and essn=ssn group by ssn;

-- question 10
SELECT count(distinct dlocation) FROM dept_locations DEPT_LOCS;

-- question 11
SELECT dname, dnumber, avg(salary), var_pop(salary) FROM employee, department where dno=dnumber group by dname, dnumber;

-- question 12
SELECT * FROM employee where salary > (SELECT max(salary) FROM employee WHERE sex='F');

-- question 13
-- part a
SELECT lname EMPLOYEE, dname, SUPERVISOR FROM employee E join department on dno=dnumber join (SELECT lname SUPERVISOR, ssn FROM employee) S on E.superssn = S.ssn;

-- part b
SELECT lname SUPERVISOR, dname, SUPERVISEE FROM employee S join department on dno=dnumber join (SELECT lname SUPERVISEE, superssn FROM employee) E on E.superssn = S.ssn order by SUPERVISOR;

-- question 14
-- part a
SELECT dname, count(pnumber) NUM_PROJS FROM department join project on dnum=dnumber group by dname;

-- part b
select dname, (select count(pnumber) from project where dnum=dnumber) NUM_PROJS from department;

-- question 15
-- part a
SELECT dname, count(pnumber) NUM_PROJS FROM department left join project on dnum=dnumber group by dname having count(pnumber) < 2;

-- part b
SELECT dname, count(pnumber) NUM_PROJS FROM department left join project on dnum=dnumber WHERE (SELECT count(pnumber) from project where dnum=dnumber) < 2 group by dname;

-- question 16
SELECT dname, (SELECT count(pnumber) FROM project WHERE dnum=dnumber) NUM_PROJS from department WHERE (SELECT count(pnumber) FROM project WHERE dnum=dnumber) < 2; 

-- question 17
SELECT dname, count(ssn) FROM department left join (SELECT * from employee where salary < (select max(salary) from employee where sex='F')) on dno=dnumber group by dname;

-- question 18
select ssn, count_employees from (SELECT ssn, (select count(ssn) from employee E where E.superssn=S.ssn) count_employees FROM employee S)
group by ssn, count_employees having count_employees > 0 and count_employees >
(select avg(count_employees) from (select ssn, count_employees from (SELECT ssn, (select count(ssn) from employee E where E.superssn=S.ssn) count_employees FROM employee S) group by ssn, count_employees having count_employees > 0));

-- question 19
SELECT dno, max(trunc(((sysdate-to_date(bdate, 'YYYY-MM-DD'))/365.25))) as MAX, min(trunc(((sysdate-to_date(bdate, 'YYYY-MM-DD'))/365.25))) as MIN from employee group by dno;

-- question 20
-- the following question is intended for an example database
-- select count(EXAMPLE_ID) from (select EXAMPLE_ID from EXAMPLE_TABLE group by EXAMPLE_ID);
