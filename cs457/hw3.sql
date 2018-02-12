-- question 7
-- single block query
SELECT lname, salary FROM employee, department WHERE dnumber != 5 and bdate != '1960-01-01';

-- join in from clause
SELECT lname, salary FROM employee JOIN department ON dno=dnumber WHERE dname != 'Research' and bdate != '1960-01-01';

-- nested query using in
SELECT lname, salary FROM employee WHERE dno in (SELECT dnumber from employee, department WHERE dname != 'Research') and bdate != '1960-01-01';

-- nested query using <> all
SELECT lname, salary FROM employee WHERE dno <>all (SELECT dnumber from employee, department WHERE dname = 'Research') and bdate != '1960-01-01';

-- correlated nested query using 'not exists'
SELECT lname, salary FROM employee WHERE not exists (SELECT dnumber from employee, department WHERE dname = 'Research' and bdate = '1960-01-01' and dno=dnumber);

-- nested query in from clause
SELECT lname, salary FROM (SELECT * FROM employee, department WHERE dno=dnumber and dname != 'Research' and bdate != '1960-01-01');

-- question 8
-- part a
SELECT lname, pno, hours FROM (SELECT * FROM employee, works_on, department WHERE dno=dnumber and dname = 'Research' and hours < 20) ORDER BY hours;

-- part b
SELECT lname, pno, hours FROM (SELECT * FROM employee LEFT JOIN works_on, department WHERE dno=dnumber and (dname = 'Research' OR dname = 'Headquarters') and hours < 20) ORDER BY hours;

-- question 9
-- part a
SELECT ssn FROM employee
MINUS
SELECT ssn FROM employee,project,works_on WHERE pname='Computerization' and pnumber=pno and essn=ssn;

-- question 10
SELECT count(dlocation) FROM dept_locations DEPT_LOCS;

-- question 11
SELECT dname, dnumber, avg(salary), var_pop(salary) FROM employee, department where dno=dnumber;

-- question 12
SELECT * FROM employee where salary > max(SELECT salary FROM employee WHERE sex='f');

-- question 13
-- part a
SELECT lname EMPLOYEE, dname, SUPERVISOR FROM employee E join department on dno=dnumber join (SELECT lname SUPERVISOR, ssn FROM employee) S on E.superssn = S.ssn;

-- part b
SELECT lname EMPLOYEE, dname, SUPERVISOR FROM employee E join department on dno=dnumber join (SELECT lname SUPERVISOR, ssn FROM employee) S on E.superssn = S.ssn;

SELECT lname SUPERVISOR, dname, SUPERVISEE FROM employee S join department on dno=dnumber join (SELECT lname SUPERVISEE, superssn FROM employee) E on E.superssn = S.ssn order by SUPERVISOR;

-- question 14
-- part a
SELECT dname, count(pnumber) NUM_PROJS FROM department join project on dnum=dnumber group by dname;

-- part b
SELECT dname, count(pnumber) NUM_PROJS FROM department, project WHERE dnum=dnumber group by dname;

-- question 15
-- part a
SELECT dname, count(pnumber) NUM_PROJS FROM department left join project on dnum=dnumber group by dname having count(pnumber) < 2;

-- part b
SELECT dname, count(pnumber) NUM_PROJS FROM department left join project on dnum=dnumber WHERE (SELECT count(pnumber) from project where dnum=dnumber) < 2 group by dname;

-- question 16
SELECT dname, (SELECT count(pnumber) cpn FROM project WHERE dnum=dnumber and cpn < 2) from department;
