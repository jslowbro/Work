package controllers

import java.sql.Timestamp

import javax.inject.{Inject, Singleton}
import models.{Item, Order, StockItem}
import play.api.libs.json.Json
import play.api.mvc.{AbstractController, ControllerComponents}
import services.DBO

@Singleton
class APIController @Inject()(cc: ControllerComponents, af: AssetsFinder, dbo: DBO)(implicit assetsFinder: AssetsFinder)
  extends AbstractController(cc)  {

  //handling Jsons of

  implicit val jsonwriterItem = Json.writes[Item]

  implicit val jsonreaderItem = Json.reads[Item]

  implicit val jsonwriterOrder = Json.writes[Order]

  implicit val jsonwriterStockItem = Json.writes[StockItem]

  implicit val jsonreaderStockItem = Json.reads[StockItem]



  //TODO DBOOOOOOOOOOOOOOOOOOOOOOOO
  val itemlist = List(
    Item("Tom",20, "S", "BLUE"),
    Item("Tom",20, "M", "GREEN"),
    Item("Tom",20, "L","BLUE"),
    Item("Tom",20, "XL","BLUE")
  )


  // APIs

  def getListOfAllItems() = {
    TODO
  }

  def getListOfItems(id: Int) = Action {
    println("Getting List of items for order No." + id)
    val json = Json.toJson(itemlist)
    Ok(json)
  }

  def getListOfOrders() = Action {
    val list = dbo.getOrderList
    val json = Json.toJson(list)

    /*//TODO Testing

    val stockItemList: List[StockItem] = List(StockItem(1,"S","RED",500), StockItem(2,"XL","BLUE",500))
    dbo.updateStock(stockItemList)*/


    Ok(json)
  }

  def postListOfItems() = Action { implicit request =>
      //parsing Json to a list
      val json  = request.body.asJson.get
      val list: List[Item] = json.as[List[Item]]
      dbo.postItems(list)
      Ok
  }

  //TODO Api's for stock managment

  def getStock() = Action {
    val list = dbo.getStock
    val json = Json.toJson(list)

    Ok(json)

  }

  def upateStockInfo() = {
    TODO
  }

}
