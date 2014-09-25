function theme_preprocess_page(&$vars, $hook) {
    drupal_set_html_head(
    '<meta charset="utf-8"/>
	   <link href="http://fonts.googleapis.com/css?family=Boogaloo" rel="stylesheet" type="text/css">
	   <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js"></script>
	   <script src="/sites/all/themes/garland/multiupload.js"></script>
  	');
    $vars['head'] .= drupal_get_html_head();	
}
