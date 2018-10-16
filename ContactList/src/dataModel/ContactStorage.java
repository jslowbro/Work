package dataModel;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import javax.xml.stream.*;
import javax.xml.stream.events.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Iterator;

public class ContactStorage {

    private static ContactStorage instance = new ContactStorage();

    private static final String CONTACT = "contact";
    private static final String FIRST_NAME = "first_name";
    private static final String LAST_NAME = "last_name";
    private static final String PHONE_NUMBER = "phone_number";
    private static final String NOTES = "notes";
    private static final String PHOTO = "photo";


    private ObservableList<Contact> contactObservableList = FXCollections.observableArrayList();
    private String filePath;

    public static ContactStorage getInstance() {
        return instance;
    }

    private ContactStorage() {
        filePath = "defaultpath.xml";
    }

    public ObservableList<Contact> getContactObservableList() {
        return contactObservableList;
    }

    public void setContactObservableList(ObservableList<Contact> contactObservableList) {
        this.contactObservableList = contactObservableList;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }


    public void loadContacts() throws IOException {
        contactObservableList = FXCollections.observableArrayList();
        Path path = Paths.get(filePath);
        BufferedReader reader = Files.newBufferedReader(path);

        String input;

        try {
            while((input = reader.readLine()) != null) {
                String[] contactPieces = input.split("\t");
                boolean favourite = false;
                if(contactPieces[4].equals("true")){
                    favourite=true;
                }

                Contact contact = new Contact(contactPieces[0],contactPieces[1], contactPieces[2], contactPieces[3], favourite);

                contactObservableList.add(contact);

            }
        } finally {
            if(reader !=null) {
                reader.close();
            }

        }
    }

    public void storeContacts() throws IOException {
        Path path = Paths.get(filePath);

        BufferedWriter writer = Files.newBufferedWriter(path);

        try {
            Iterator<Contact> iterator = contactObservableList.iterator();
            while (iterator.hasNext()) {
                Contact contact = iterator.next();
                writer.write(String.format("%s\t%s\t%s\t%s\t%s", contact.getName(), contact.getSurname(), contact.getNumber(), contact.getPhotoPath(), contact.isFavourite()));
                writer.newLine();
            }
        } finally {
            if(writer != null ) {
                writer.close();
            }
        }
    }

    public void loadContactsXML() {
        try {
            // First, create a new XMLInputFactory
            XMLInputFactory inputFactory = XMLInputFactory.newInstance();
            // Setup a new eventReader
            InputStream in = new FileInputStream(filePath);
            XMLEventReader eventReader = inputFactory.createXMLEventReader(in);
            // read the XML document
            Contact contact = null;

            while (eventReader.hasNext()) {
                XMLEvent event = eventReader.nextEvent();

                if (event.isStartElement()) {
                    StartElement startElement = event.asStartElement();
                    // If we have a contact item, we create a new contact
                    if (startElement.getName().getLocalPart().equals(CONTACT)) {
                        contact = new Contact();
                        continue;
                    }

                    if (event.isStartElement()) {
                        if (event.asStartElement().getName().getLocalPart()
                                .equals(FIRST_NAME)) {
                            event = eventReader.nextEvent();
                            contact.setName(event.asCharacters().getData());
                            continue;
                        }
                    }
                    if (event.asStartElement().getName().getLocalPart()
                            .equals(LAST_NAME)) {
                        event = eventReader.nextEvent();
                        contact.setSurname(event.asCharacters().getData());
                        continue;
                    }

                    if (event.asStartElement().getName().getLocalPart()
                            .equals(PHONE_NUMBER)) {
                        event = eventReader.nextEvent();
                        contact.setNumber(event.asCharacters().getData());
                        continue;
                    }

                    if (event.asStartElement().getName().getLocalPart()
                            .equals(NOTES)) {
                        event = eventReader.nextEvent();
                        if(event.asCharacters().getData().equals("true")){
                            contact.setFavourite(true);
                        } else {
                            contact.setFavourite(false);
                        }
                        continue;
                    }
                    if (event.asStartElement().getName().getLocalPart()
                            .equals(PHOTO)) {
                        event = eventReader.nextEvent();
                        if(event.asCharacters().getData() != null){
                            contact.setPhotoPath(event.asCharacters().getData());
                        } else {
                            contact.setPhotoPath("NullPhotoPath");
                        }
                        continue;
                    }

                }

                // If we reach the end of a contact element, we add it to the list
                if (event.isEndElement()) {
                    EndElement endElement = event.asEndElement();
                    if (endElement.getName().getLocalPart().equals(CONTACT)) {
                        try{
                            contactObservableList.add(contact);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }

                    }
                }
            }
        }
        catch (FileNotFoundException e) {
            //e.printStackTrace();
        }
        catch (XMLStreamException e) {
            e.printStackTrace();
        }
    }

    public void saveContactsXML() {

        try {
            // create an XMLOutputFactory
            XMLOutputFactory outputFactory = XMLOutputFactory.newInstance();
            // create XMLEventWriter
            XMLEventWriter eventWriter = outputFactory
                    .createXMLEventWriter(new FileOutputStream(filePath));
            // create an EventFactory
            XMLEventFactory eventFactory = XMLEventFactory.newInstance();
            XMLEvent end = eventFactory.createDTD("\n");
            // create and write Start Tag
            StartDocument startDocument = eventFactory.createStartDocument();
            eventWriter.add(startDocument);
            eventWriter.add(end);

            StartElement contactsStartElement = eventFactory.createStartElement("",
                    "", "contacts");
            eventWriter.add(contactsStartElement);
            eventWriter.add(end);

            for (Contact contact: contactObservableList) {
                saveContactXML(eventWriter, eventFactory, contact);
            }

            eventWriter.add(eventFactory.createEndElement("", "", "contacts"));
            eventWriter.add(end);
            eventWriter.add(eventFactory.createEndDocument());
            eventWriter.close();
        }
        catch (FileNotFoundException e) {
            System.out.println("Problem with Contacts file: " + e.getMessage());
            e.printStackTrace();
        }
        catch (XMLStreamException e) {
            System.out.println("Problem writing contact: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private void saveContactXML(XMLEventWriter eventWriter, XMLEventFactory eventFactory, Contact contact)
            throws FileNotFoundException, XMLStreamException {

        XMLEvent end = eventFactory.createDTD("\n");

        // create contact open tag
        StartElement configStartElement = eventFactory.createStartElement("",
                "", CONTACT);
        eventWriter.add(configStartElement);
        eventWriter.add(end);
        // Write the different nodes
        createNodeXML(eventWriter, FIRST_NAME, contact.getName());
        createNodeXML(eventWriter, LAST_NAME, contact.getSurname());
        createNodeXML(eventWriter, PHONE_NUMBER, contact.getNumber());
        if(contact.isFavourite()){
            createNodeXML(eventWriter, NOTES, "true");
        } else {
            createNodeXML(eventWriter, NOTES, "false");
        }
        createNodeXML(eventWriter, PHOTO, contact.getPhotoPath());


        eventWriter.add(eventFactory.createEndElement("", "", CONTACT));
        eventWriter.add(end);
    }

    private void createNodeXML(XMLEventWriter eventWriter, String name,
                            String value) throws XMLStreamException {

        XMLEventFactory eventFactory = XMLEventFactory.newInstance();
        XMLEvent end = eventFactory.createDTD("\n");
        XMLEvent tab = eventFactory.createDTD("\t");
        // create Start node
        StartElement sElement = eventFactory.createStartElement("", "", name);
        eventWriter.add(tab);
        eventWriter.add(sElement);
        // create Content
        Characters characters = eventFactory.createCharacters(value);
        eventWriter.add(characters);
        // create End node
        EndElement eElement = eventFactory.createEndElement("", "", name);
        eventWriter.add(eElement);
        eventWriter.add(end);
    }

}
