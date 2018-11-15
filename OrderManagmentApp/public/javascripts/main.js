/*
var dataContainer = document.getElementById("data-info");
var btn = document.getElementById("btn");

btn.addEventListener("click", function () {
    var myRq = new XMLHttpRequest();
    //myRq.open('GET','https://learnwebcode.github.io/json-example/animals-1.json');
    myRq.open('GET', 'http://localhost:9000/listitems');
    myRq.onload = function () {
        /!*console.log(myRq.responseText);*!/
        var myData = JSON.parse(myRq.responseText);
        renderItems(myData)
        //renderAnimals(myData)

    };
    myRq.send();
});

function renderAnimals(data) {
    var htmlString = "";

    for(i = 0; i < data.length ; i++ ) {
        htmlString += "<p>" + data[i].name + " is a " + data[i].species + ".</p>";
    }

    dataContainer.insertAdjacentHTML('beforeend',htmlString)
}

function renderItems(data) {
    var htmlString="";

    for(i=0; i< data.length; i++){
        htmlString += "<p>" + data[i].name + " " + data[i].name + " " + data[i].name + " " + data[i].name + ".</p>";
    }
    dataContainer.insertAdjacentHTML('beforehand', htmlString)
}
*/


var json= "";
var dataContainer = document.getElementById("get-info");
var btn = document.getElementById("btn");
var btn2 = document.getElementById("btn2");

btn.addEventListener("click", function () {
    var getRequest = new XMLHttpRequest();
    //myRq.open('GET','https://learnwebcode.github.io/json-example/animals-1.json');
    getRequest.open('GET', 'http://localhost:9000/listitems');
    getRequest.onload = function () {
        console.log(getRequest.responseText);
        var myData = JSON.parse(getRequest.responseText);
        renderItems(myData)
        //renderAnimals(myData)

    };
    getRequest.send();
});

btn2.addEventListener("click", function () {
    var getRequest = new XMLHttpRequest();
    var rqData = "not initialized";
    getRequest.open('GET', 'http://localhost:9000/createItem');
    getRequest.onload = function () {
        var responseText = getRequest.responseText;
        rqData = responseText.toString();
        console.log(responseText);
        postItems(rqData)
    };
    getRequest.send();

});


function renderItems(data) {
    var htmlString="";

    for(i=0; i< data.length; i++){
        htmlString += "<p>" + data[i].name + " " + data[i].age + " " + data[i].color + " " + data[i].size+ ".</p>";
    }
    dataContainer.insertAdjacentHTML('beforeend', htmlString)
}
function postItems(data) {
    var xhr = new XMLHttpRequest();
    var url = 'http://localhost:9000/postitems';
    xhr.open('POST', url, true);
    xhr.setRequestHeader("Content-Type", "application/json");
    xhr.onreadystatechange = function () {
        if(xhr.readyState == 4 && xhr.status == 200) {
            alert(xhr.responseText);
        }
    };
    xhr.send(data)
}

/*btn2.addEventListener("click", function () {
    $.ajax({
        url: "http://localhost:9000/postitems",
        type: "POST",
        data: { apiKey: "23462", method: "POST", ip: "208.74.35.5" },
        dataType: "json",
        success: function (result) {
            switch (result) {
                case true:
                    processResponse(result);
                    break;
                default:
                    resultDiv.html(result);
            }
        },
        error: function (xhr, ajaxOptions, thrownError) {
            alert(xhr.status);
            alert(thrownError);
        }
    });
});*/


