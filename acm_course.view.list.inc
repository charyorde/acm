<?php
function course_list(){
	$content = '<div class="block" >'.drupal_get_form('acm_course_search_form').'</div>';
	$content .= '<div style="clear:both" ></div>';
	$header = array(
		array('data' => t('Id'), 'field' => 'id', 'sort' => 'asc'),
		array('data' => t('Title'),'field' => 'title', 'sort' => 'asc'),
		array('data' => t('Code'),'field' => 'Code', ),
		array('data' => t('Test Score'),'field' => 'test_score', ),
		//array('data' => t('Submitted by'),'field' => 'submittedby', ),	
		array('data' => t('View')),
		array('data' => t('Update')),
	);
	$id = $_GET['ono'];
	if(!empty($_GET['ono'])){
		$Sql="SELECT c.id,c.title,c.code,c.test_score FROM acm_course c where c.id =".$id;
	}
	else{
		$Sql="SELECT c.id,c.title,c.code,c.test_score FROM acm_course c";
	}
	$count = "SELECT count(*) FROM acm_course";	
	$query = pager_query($Sql,5,0,$count);
	while($row = db_fetch_object($query)){
	   $data[] = array( $row->id, $row->title,$row->code,$row->test_score, l('View', 'student/course/'.$row->id.'/view'), l('Edit','student/course/update/', array('query'=>array('acmID'=>$row->id))));
	}
	$content .= theme('table', $header, $data);
	$content .= theme('pager', 5);
	return $content;
}

function acm_course_search_form($form_id){
	$form['#method'] = 'get';
	$form['#token'] = FALSE;
	$form['#form_build_id'] = FALSE;
	$form['#form_id'] = FALSE;
	$form['ono'] = array(
		'#type' => 'textfield',
		'#title' => t('View order number'),
		'#attributes' => array( 'maxlength' => '128', 'size'=> '30'),
		'#prefix' => '<div class="form-inline views-exposed-form"> <div class="views-exposed-widget">',
		'#suffix' => '</div>',
		'#default_value' => isset($_GET['ono'])?$_GET['ono']:'',
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#attributes' => array( 'name' => ''),
		'#prefix' => '<div class="views-exposed-widget">',
		'#suffix' => '</div></div>',
		'#value' => 'Apply',
	 );  
	
	return $form;
}

function acm_course_update(){
	return drupal_get_form('acm_course_update_form');
	}
function acm_course_update_form($form_id){
	$acm_id = $_GET['acmID'];	
	$query = db_query("SELECT c.id,c.exam_score,c.test_score,c.academic_departmentid,c.title,c.code,c.description,c.creditpoint,c.prerequisitecodes,c.prerequisites,c.level,c.semester,c.session,c.lecturerincharge,c.numberofcas,c.caapprovalmethod,c.maxtestmark,c.maxexammark,c.programme,c.type,c.created,c.updated FROM acm_course c where c.id=".$acm_id);
	$row = db_fetch_object($query);
	$form['title'] = array(
		'#title' => t('Title'),
		'#type' => 'textfield',
		'#required' => TRUE,
		'#default_value' => isset($row->title)? $row->title:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['exam_score'] = array(
		'#title' => t('Exam Score'),
		'#type' => 'textfield', 
		'#default_value' => isset($row->exam_score)? $row->exam_score:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['test_score'] = array(
		'#title' => t('Test Score'),
		'#type' => 'textfield',
		'#default_value' => isset($row->test_score)? $row->test_score:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>' ,     
	);
	$form['academic_departmentid'] = array(
		'#title' => t('Academic Department Id'),
		'#type' => 'textfield',
		'#default_value' => isset($row->academic_departmentid)? $row->academic_departmentid:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['code'] = array(
		'#title' => t('Code'),
		'#type' => 'textfield',
		'#default_value' => isset($row->code)? $row->code:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['description'] = array(
		'#title' => t('Description'),
		'#type' => 'textarea',
		'#default_value' => isset($row->description)? $row->description:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['creditpoint'] = array(
		'#title' => t('Credit Point'),
		'#type' => 'textfield',
		'#default_value' => isset($row->creditpoint)? $row->creditpoint:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['prerequisitecodes'] = array(
		'#title' => t('Prerequisite Codes'),
		'#type' => 'textfield',
		'#default_value' => isset($row->prerequisitecodes)? $row->prerequisitecodes:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['prerequisites'] = array(
		'#title' => t('Prerequisite Course'),
		'#type' => 'textfield',
		'#default_value' => isset($row->prerequisites)? $row->prerequisites:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['level'] = array(
		'#title' => t('Level'),
		'#type' => 'textfield',
		'#default_value' => isset($row->level)? $row->level:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['semester'] = array(
		'#title' => t('Semester'),
		'#type' => 'textfield',
		'#default_value' => isset($row->semester)? $row->semester:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['session'] = array(
		'#title' => t('Session'),
		'#type' => 'textfield',
		'#default_value' => isset($row->session)? $row->session:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['lecturerincharge'] = array(
		'#title' => t('Lecturer in Charge'),
		'#type' => 'textfield',
		'#default_value' => isset($row->lecturerincharge)? $row->lecturerincharge:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['numberofcas'] = array(
		'#title' => t('Number of CAS'),
		'#type' => 'textfield',
		'#default_value' => isset($row->numberofcas)? $row->numberofcas:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['caapprovalmethod'] = array(
		'#title' => t('CA Approval Method'),
		'#type' => 'textfield',
		'#default_value' => isset($row->caapprovalmethod)? $row->caapprovalmethod:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['maxtestmark'] = array(
		'#title' => t('Max Test Mark'),
		'#type' => 'textfield',
		'#default_value' => isset($row->maxtestmark)? $row->maxtestmark:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['maxexammark'] = array(
		'#title' => t('Max Exam Mark'),
		'#type' => 'textfield',
		'#default_value' => isset($row->maxexammark)? $row->maxexammark:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['programme'] = array(
		'#title' => t('Programme'),
		'#type' => 'textfield',
		'#default_value' => isset($row->programme)? $row->programme:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$options = array('Core'=>'Core','Elective'=>'Elective','Required'=>'Required');
	$form['type'] = array(
		'#title' => t('Type'),
		'#type' => 'select',
		'#options' => $options,
		'#default_value' => isset($row->type)? $row->type:'',
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	
	$form['updated'] = array(
		'#title' => t('Updated'),
		'#type' => 'hidden',
		'#default_value' => date("Y-m-d H:i:s"),
	);
	$form['submit'] = array(
		'#value' => 'Update',
		'#type' => 'submit',
		'#submit' => array('acm_course_update_form_submit'),
		'#prefix' => '<div class="member_submit" >',
		'#suffix' => '</div>',
	);
	return $form;
	}
function acm_course_update_form_submit($form, &$form_state){
	$values = $form_state['values'];	$update="title='$values[title]',exam_score='$values[exam_score]',test_score='$values[test_score]',academic_departmentid='$values[academic_departmentid]',code='$values[code]',description='$values[description]',creditpoint='$values[creditpoint]',prerequisitecodes='$values[prerequisitecodes]',prerequisites='$values[prerequisites]',level='$values[level]',semester='$values[semester]',session='$values[session]',lecturerincharge='$values[lecturerincharge]',numberofcas='$values[numberofcas]',caapprovalmethod='$values[caapprovalmethod]',maxtestmark='$values[maxtestmark]',maxexammark='$values[maxexammark]',programme='$values[programme]',type='$values[type]',updated='$values[updated]'";
	$acm_id = $_GET['acmID'];
	$res=update_sql("UPDATE {acm_course} SET $update WHERE id =".$acm_id);
	if($res){
	drupal_goto('student/course/list');
	}
}

function view_courselist($id){
	$output ="<div></div>" ;	
	$output .="<div class='title'><h3>Course Details</h3></div>" ;	
	$output .= "<table class='course_details' cellpadding='4' width='100%'>" ;
		
	$query = db_query("SELECT c.id,c.exam_score,c.test_score,c.academic_departmentid,c.title,c.code,c.description,c.creditpoint,c.prerequisitecodes,c.prerequisites,c.level,c.semester,c.session,c.lecturerincharge,c.numberofcas,c.caapprovalmethod,c.maxtestmark,c.maxexammark,c.programme,c.type,c.created,c.updated FROM acm_course c where c.id=".$id);
	$row = db_fetch_object($query);
	if($row->title){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Course Title:</td><td>".$row->title."</td></tr>";
	}
	if($row->exam_score){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Exam Score:</td><td>".$row->exam_score."</td></tr>";
	}
	if($row->test_score){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Test Score:</td><td>".$row->test_score."</td></tr>";
	}
	if($row->academic_departmentid){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Academic Department Id:</td><td>".$row->academic_departmentid."</td></tr>";
	}
	if($row->code){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Code:</td><td>".$row->code."</td></tr>";
	}
	if($row->description){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Description:</td><td>".$row->description."</td></tr>";
	}
	if($row->creditpoint){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Credit Point:</td><td>".$row->creditpoint."</td></tr>";
	}
	if($row->prerequisitecodes){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Prerequisite Codes:</td><td>".$row->prerequisitecodes."</td></tr>";
	}
	if($row->prerequisites){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Prerequisites:</td><td>".$row->prerequisites."</td></tr>";
	}
	if($row->level){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Level:</td><td>".$row->level."</td></tr>";
	}
	if($row->semester){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Semester:</td><td>".$row->semester."</td></tr>";
	}
	if($row->lecturerincharge){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Lecturer in Charge:</td><td>".$row->lecturerincharge."</td></tr>";
	}
	if($row->numberofcas){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Number of CAS:</td><td>".$row->numberofcas."</td></tr>";
	}
	if($row->caapprovalmethod){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>CA Approval Method:</td><td>".$row->caapprovalmethod."</td></tr>";
	}
	if($row->maxtestmark){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Max Test Mark:</td><td>".$row->maxtestmark."</td></tr>";
	}
	if($row->maxexammark){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Max Exam Mark:</td><td>".$row->maxexammark."</td></tr>";
	}
	if($row->programme){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Programme:</td><td>".$row->programme."</td></tr>";
	}
	if($row->type){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Type:</td><td>".$row->type."</td></tr>";
	}
	if($row->created){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Created:</td><td>".$row->created."</td></tr>";
	}
	$output.= '</table>';
	
 return $output;
}
