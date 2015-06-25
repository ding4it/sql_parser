this is a sql parser.
only allow SELECT FROM WHERE


select a from b;

select a from b where c = d;

select a,b,c from table1 where a = 1;

select a,b,c from table1, (select hh from dd) as dt where a > c;
