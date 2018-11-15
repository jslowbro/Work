function PostsListController(mainSvc) {
    var vm = this;


    mainSvc.getPosts().then(function(response) {
        vm.posts = response.data;
    });

}



app.component('postsList', {
   templateUrl: 'posts_list/post_list.html',
    controller: PostsListController,
    controllerAs: 'vm'
});