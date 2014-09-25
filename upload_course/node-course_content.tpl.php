<script>
var uploadfile = '<?php print $GLOBALS['base_url']."/".path_to_theme() ?>' ;
var nid = '<?php print $node->nid ?>';
var config = {
	support : "image/jpg,image/png,image/bmp,image/jpeg,image/gif,application/msword,application/vnd.openxmlformats-officedocument.wordprocessingml.document,application/vnd.ms-excel,application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",		// Valid file formats
	form: "demoFiler",					// Form ID
	dragArea: "dragAndDropFiles",		// Upload Area ID
	uploadUrl: nid+"/upload"            // Server side upload url
}
$(document).ready(function(){
	initMultiUploader(config);
});
</script>
<?php
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">

<?php print $picture ?>

<?php if ($page == 0): ?>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

  <?php if ($submitted): ?>
    <span class="submitted"><?php print $submitted; ?></span>
  <?php endif; ?>

  <?php //need to add in course content .tpl file
	 if($node->title=='Course Materials'){
	 global $user;
	 if(!in_array('anonymous user',$user->roles)){
	 ?>
	<div class="course_uploadlink">
		<a href = "javascript:void(0)" onclick = "document.getElementById('light').style.display='block';document.getElementById('fade').style.display='block'">Upload</a>
	</div>
	<?php } }?>
		<div id="light" class="popup_content">
			<div id="dragAndDropFiles" class="uploadArea">
				<h1>Drop Course Materials Here</h1>
			</div>
			<div class="upload_wrapper">
				<form name="demoFiler" id="demoFiler" enctype="multipart/form-data">
					<input type="file" name="multiUpload" id="multiUpload" multiple />
					<input type="submit" name="submitHandler" id="submitHandler" value="Upload" class="buttonUpload" />
				</form>
			</div>
			<div class="progressBar">
					<div class="status"></div>
			</div>
			<div class="upload_wrapper_close">
				<a href = "<?php print '/node/'.$node->nid?>" onclick = "document.getElementById('light').style.display='none';document.getElementById('fade').style.display='none'">Close</a>
			</div>
		</div>
    <div id="fade" class="black_overlay"></div>
	
  <div class="content clear-block">
    <?php print $content ?>
  </div>

  <div class="clear-block">
    <div class="meta">
    <?php if ($taxonomy): ?>
      <div class="terms"><?php print $terms ?></div>
    <?php endif;?>
    </div>

    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>

</div>
