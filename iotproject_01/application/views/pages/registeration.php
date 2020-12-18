<h2 class="maintitle"><?= $title ?></h2>


<form action="/users/create" method="post">

    <label for="title">Title</label>
    <input type="input" name="title" /><br />

    <label for="body">Text</label>
    <textarea name="body"></textarea><br />

    <input type="submit" name="submit" value="Create news item" />

</form>