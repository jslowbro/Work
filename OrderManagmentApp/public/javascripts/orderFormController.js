var app = angular.module('OrderFormApp', []);

app.controller('mainCtrl', function($scope, $http) {

    $scope.colors = ["RED", "BLUE", "GREEN"];
    $scope.colorValue = "RED";
    $scope.sizeList = ["S", "M", "L", "XL"];
    $scope.sizeValue = "S";
    $scope.master = {name: "", age: ""};

    $scope.itemlist = [];

    $scope.addItem = function() {
        //pushing item on the list
        var item = {name: angular.copy($scope.user.name),
                    age: angular.copy($scope.user.age),
                    size: angular.copy($scope.sizeValue),
                    color: angular.copy($scope.colorValue)};

        $scope.itemlist.push(item);
        //clearing form
        $scope.user = angular.copy($scope.master);
    };

    $scope.testData = function () {
        console.log($scope.colorValue);
        console.log($scope.sizeValue);
        console.log($scope.user.name);
        console.log($scope.user.age);
    };

    $scope.sendData = function () {
        /*var req = {
            method: 'POST',
            url: 'http://localhost:9000/postitems',
            headers: {
                'Content-Type': 'application/json'
            },
            data: JSON.stringify($scope.itemlist[0])
        };
        $http(req).then(function(){
            console.log("Success")
        }, function(){
            console.log("Failure")
        });*/
        var xhr = new XMLHttpRequest();
        var url = 'http://localhost:9000/postitems';
        xhr.open('POST', url, true);
        xhr.setRequestHeader("Content-Type", "application/json");
        xhr.onreadystatechange = function () {
            if(xhr.readyState == 4 && xhr.status == 200) {
                alert(xhr.responseText);
            }
        };
        xhr.send(JSON.stringify($scope.itemlist[0]))
    };



});


function fetchAllElements() {

}