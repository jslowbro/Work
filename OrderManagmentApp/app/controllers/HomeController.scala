package controllers

import java.util

import javax.inject._
import models.Item
import play.api.mvc._
import services.DBO
import play.api.libs.json
import play.api.libs.json.{JsResult, JsSuccess, JsValue, Json}
import views.html.main


/**
 * This controller creates an `Action` to handle HTTP requests to the
 * application's home page.
 */
@Singleton
class HomeController @Inject()(cc: ControllerComponents, af: AssetsFinder) (implicit assetsFinder: AssetsFinder)
  extends AbstractController(cc) {



  val itemlist = List(
    Item("Tom",20, "S", "BLUE"),
    Item("Tom",20, "M", "GREEN"),
    Item("Tom",20, "L","BLUE"),
    Item("Tom",20, "XL","BLUE")
  )



  /**
   * Create an Action to render an HTML page with a welcome message.
   * The configuration in the `routes` file means that this method
   * will be called when the application receives a `GET` request with
   * a path of `/`.
   */
  implicit val jsonwriter = Json.writes[Item]

  implicit val jsonreader = Json.reads[Item]

  def listItems1() = Action {
    val json = Json.toJson(itemlist)
    Ok(json)
  }
  def listItems2() = Action {
    Ok(views.html.Home.jsonTesting())
  }


  def createItemJson() = Action {
    val item: Item = Item("GGGGGG", 20, "XXXX", "XXXXX")
    val json = Json.toJson(item)
    Ok(json)
  }

  def postitems() = Action { implicit request =>
    val json  = request.body.asJson.get
    val item = json.as[Item]
    println(item + "  POST request actually working")
    Ok
  }
  def getmainJs()= Action {
    Ok
  }

  def index = Action {
    Ok(views.html.index("Hello from default view"))
  }

  def welcome(name: String, lastName: String) = Action {
    Ok(views.html.Home.welcome(name,lastName))
  }

  def jstest() = Action {
    Ok(views.html.Home.sampleJavaScript(new util.ArrayList[Item]()))
  }

  def items() = Action {
    val list = DBO.list
    Ok(views.html.itemindex(list))
  }


  /*def reads(json: JsValue) : JsResult[Item] = {
    val name: String = (json \ "name").as[String]
    val age: Int = (json \ "age").as[Int]
    val size: String = (json \ "size").as[String]
    val color: String = (json \ "color").as[String]
    JsSuccess(Item(name,age,size,color))
  }*/


}
