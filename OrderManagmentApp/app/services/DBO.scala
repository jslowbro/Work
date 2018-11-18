package services

import java.sql._

import javax.inject.Inject
import models.{Item, Order}
import play.api.db._
import play.api.mvc.{BaseController, ControllerComponents}

import scala.collection.mutable.ListBuffer

class DBO @Inject()(db: Database, val controllerComponents: ControllerComponents) extends BaseController {

  /*val list: List[Item] = new ArrayList[Item]*/
  val url = "jdbc:mysql://localhost/shoesdb"
  val driver = "com.mysql.jdbc.Driver"
  val username = "root"
  val password = ""


  //loadFromMySQLDatabase

 /* def loadFromMySQLDatabase = {

    val connection: Connection = DriverManager.getConnection(url, username, password)
    try {
      Class.forName(driver)
      val statement = connection.createStatement
      val rs = statement.executeQuery("SELECT * FROM items")
      while (rs.next) {
        var item: Item = Item(rs.getString("name"), rs.getInt("age"), rs.getString("size"), rs.getString("color"))
        list.add(item)

      }

    } catch {
      case e: Exception => e.printStackTrace
        println("Couldn't access database")
    } finally {
      connection.close()
    }
    println(list)

  }*/

  def helloWorld = {
    val conn = db.getConnection()

    try{
      val statement = conn.createStatement()
      val rs = statement.executeQuery("SELECT * FROM items")

      while(rs.next()){
        val item: Item = Item(rs.getString("name"), rs.getInt("age"), rs.getString("size"), rs.getString("color"))
        println(item)
      }
    } catch {
      case e: Exception => e.printStackTrace()
    } finally {
      conn.close()
    }

  }

  def postItems(list: List[Item]) = {
    val conn = db.getConnection()

    try {
      //new Order
      val insertOrderPrepQuery = "INSERT INTO orders(timestamp) VALUES(?)"
      val statement1 = conn.prepareStatement(insertOrderPrepQuery)
      statement1.setTimestamp(1, new Timestamp(System.currentTimeMillis()))
      statement1.execute()
      //get new Order Id
      val getThatOrderId = "SELECT COUNT(*) FROM orders"
      val statement2 = conn.createStatement()
      val resultSet2 = statement2.executeQuery(getThatOrderId)
      resultSet2.next()
      val count = resultSet2.getInt(1)
      //adding List of Items assigned to an Order
      for(item <- list){
        val insertItemPrepQuery = "INSERT INTO items(name,age,size,color,order_id) VALUES(?,?,?,?,?)"
        val statement3 = conn.prepareStatement(insertItemPrepQuery)
        statement3.setString(1, item.name )
        statement3.setInt(2, item.age)
        statement3.setString(3, item.size )
        statement3.setString(4, item.color )
        statement3.setInt(5, count)
        statement3.execute()
      }

    } catch {
      case e: Exception => e printStackTrace()
    } finally {
      conn.close()
    }
  }

  def getOrderList: List[Order] = {
    val conn = db.getConnection()
    val tempOrderList = ListBuffer[Order]()
    val finOrderList = ListBuffer[Order]()



    try {
      //getting all Orders
      val getAllOrdersQuery = "SELECT * FROM orders"
      val getOrdersStatement = conn.createStatement()
      val ordersResultSet = getOrdersStatement.executeQuery(getAllOrdersQuery)
      while(ordersResultSet.next()){
        val order = Order(ordersResultSet.getInt("id"), ordersResultSet.getTimestamp("timestamp").toString, List())
        tempOrderList += order
      }

      //Assigning itemLists to each order
      for(order <- tempOrderList){
        //getting the itemlist assigned to an order
        val prepGetItemsByOrderId = "SELECT * FROM `orders` JOIN `items` ON order_id = orders.id WHERE orders.id = ?"
        val getItemsByOrderIdStmnt = conn.prepareStatement(prepGetItemsByOrderId)
        getItemsByOrderIdStmnt.setInt(1,order.id)
        val itemsResultSet = getItemsByOrderIdStmnt.executeQuery()
        //populating the list
        val itemList: ListBuffer[Item] = ListBuffer[Item]()
        while(itemsResultSet.next()){
          val item: Item = Item(itemsResultSet.getString("name"), itemsResultSet.getInt("age"), itemsResultSet.getString("size"), itemsResultSet.getString("color"))
          itemList += item
        }
        //adding the Order with the correct item List
        finOrderList += Order(order.id, order.timestamp, itemList.toList)
      }

    } catch {
      case e: Exception => e.printStackTrace()

    } finally {
      conn.close()

    }
    finOrderList.toList
  }





}
