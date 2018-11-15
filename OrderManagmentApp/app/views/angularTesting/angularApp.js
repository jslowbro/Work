var app = angular.module('AngularApp', []);

app.controller('mainCtrl', function (mainSvc) {
    
    var vm = this;
    
    this.hello = {name: "Jan", surname: "Chabik"};

    this.fruits = ['apple', 'orange', 'grape'];


    



});

app.filter('makePlural', function () {
   return function (input) {
       return input + "s";
   }
});


app.service( 'mainSvc', function ($http) {
    this.getPosts = function () {
        return $http.get('https://jsonplaceholder.typicode.com/posts');
    }
    
});