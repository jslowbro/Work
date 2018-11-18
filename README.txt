****
All projects have their respective branches
****
Documentation can be found in docs branch
****
This is my very first project using Scala, Play and AngularJS so feel free to point any mistakes. The app lets users
choose multiple items(Not specified but I've decided it would be shoes) and order them. It also allows users to view all
the previous orders. 
****
The template for this project was the starter play project which Play provides at it's website. There are many 'leftover' files 
I am hesitant to delete them since they might prove useful later. 
****
||||||SETUP||||||
1. Setup the database server using the database script that can be found at sql-scripts directory. I recommend you 
stick with the deflaut server. I've used WAMPServer or MySQLWorkBench.
2. Make sure you have the right config to access your database. It can be changed in conf/application.conf

	Deflaut config is:

  default.driver=com.mysql.jdbc.Driver
  default.url="jdbc:mysql://localhost/shoesdb"
  default.username=root
  default.password=""
3. Make sure to update sbt and check all the dependancies.
4. Make sure to run the server on port :9000 since all of the GET/POST requests are set up that way.
5. Run from the console. 
- Go into the project directory and type following commands
- sbt
- compile
- run
6. Unless I've missed something you should be good to go. Enjoy
****
All Credit goes to @JanChabik
****
