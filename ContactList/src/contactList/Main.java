package contactList;

import dataModel.ContactStorage;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("../resources/gui/mainWindow.fxml"));
        primaryStage.setTitle("Contact List App");
        primaryStage.setScene(new Scene(root, 800, 600));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }


    @Override
    public void stop() throws Exception {
        /*try {
            //TodoData.getInstance().storeTodoItems();
            //ContactStorage.getInstance().storeContacts();

        } catch (IOException e) {
            System.out.println(e.getMessage());
        }*/
        if(ContactStorage.getInstance().getLoadtype().equals("XML")){
            ContactStorage.getInstance().saveContactsXML();
        } else if(ContactStorage.getInstance().getLoadtype().equals("Database")){
            ContactStorage.getInstance().saveContactsDB();
        }

    }

    @Override
    public void init() throws Exception {
        /*try {
            //TodoData.getInstance().loadTodoItems();
            //ContactStorage.getInstance().loadContacts();

        } catch (IOException e){
            System.out.println(e.getMessage());
        }*/

        /*ContactStorage.getInstance().loadContactsXML();*/
        /*try {
            Connection connection = DriverManager.getConnection("jdbc:sqlite:C:\\Users\\Janek\\Documents\\GitHub\\contactsDatabase.db");
            Statement statement = connection.createStatement();

            *//*statement.execute("CREATE TABLE IF NOT EXISTS " +
                    "contacts(name TEXT, surname TEXT, number TEXT, favourite TEXT, photo TEXT)");
            statement.execute("INSERT INTO contacts (name,surname,number,favourite,photo)" +
                    "VALUES('Mateusz','Morawiecki','000000000','false','somedefaultpath')," +
                    "('Zbyszko','Bogdaniec','1111111','false','somedefaultpath')," +
                    "('Anna','Jagienkowna','88888888','false','somedefaultpath')");*//*


            statement.close();
            connection.close();
        } catch (SQLException e) {
            System.out.println("Something went wrong" + e.getMessage());
        }*/
    }
}
