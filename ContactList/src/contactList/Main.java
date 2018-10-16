package contactList;

import dataModel.ContactStorage;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

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
        ContactStorage.getInstance().saveContactsXML();
    }

    @Override
    public void init() throws Exception {
        /*try {
            //TodoData.getInstance().loadTodoItems();
            //ContactStorage.getInstance().loadContacts();

        } catch (IOException e){
            System.out.println(e.getMessage());
        }*/

        ContactStorage.getInstance().loadContactsXML();
    }
}
