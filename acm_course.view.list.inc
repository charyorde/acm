<?php
function course_list(){
	$content = '<div class="block" ></div>';
	$content .= '<div style="clear:both" ></div>';
	$header = array(
		array('data' => t('Id'), 'field' => 'id', 'sort' => 'asc'),
		array('data' => t('Student'),'field' => 'uid', 'sort' => 'asc'),
		array('data' => t('Grade'),'field' => 'grade', ),
		array('data' => t('Total score'),'field' => 'totalscore', ),
		array('data' => t('Submitted by'),'field' => 'submittedby', ),	
		array('data' => t('View')),
		array('data' => t('Update')),
	);
	$count = "SELECT count(*) FROM acm_course";	
	$Sql=" SELECT c.id,c.uid,c.matriculationnumber,c.currentgpa,c.totalscore,c.grade,c.gradepoint,c.dropped,c.creditload,c.approved,c.submitted,c.submittedby FROM acm_course c ";
	$query = pager_query($Sql,5,0,$count);
	while($row = db_fetch_object($query)){
	   $user=user_load($row->uid);
	   $stud=$user->name;
	   $data[] = array( $row->id, $stud,$row->grade,$row->totalscore,$row->submittedby, l('View', 'student/course/'.$row->id.'/view'),l('Edit','student/course/update/',array('query'=>array('course'=>$row->id))) );
	}
	$content .= theme('table', $header, $data);
	$content .= theme('pager', 5);
	return $content;
}

function viewsdata($id){
	$output ="<div></div>" ;	
	$output .="<div class='title'><h3>Course Details</h3></div>" ;	
	$output .= "<table class='course_details' cellpadding='4' width='100%'>" ;
		
	$query = db_query("SELECT c.id,c.exam_score,c.test_score,u.name,c.matriculationnumber,c.currentgpa,c.totalscore,c.grade,c.gradepoint,c.dropped,c.creditload,c.approved,c.submitted,c.submittedby FROM acm_course c,content_type_course_content ctc, users u WHERE c.course=ctc.nid AND c.uid=u.uid AND c.id=".$id);
	$row = db_fetch_object($query);

	if($row->name){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Student Name:</td><td>".$row->name."</td></tr>";
	}
	if($row->exam_score){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Exam Score:</td><td>".$row->exam_score."</td></tr>";
	}
	if($row->test_score){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Test Score:</td><td>".$row->test_score."</td></tr>";
	}
	if($row->title){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Course:</td><td>".$row->title."</td></tr>";
	}
	if($row->matriculationnumber){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Matriculation Number:</td><td>".$row->matriculationnumber."</td></tr>";
	}
	if($row->currentgpa){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Current GPA:</td><td>".$row->currentgpa."</td></tr>";
	}
	if($row->totalscore){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Total Score:</td><td>".$row->totalscore."</td></tr>";
	}
	if($row->grade){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Grade:</td><td>".$row->grade."</td></tr>";
	}
	if($row->gradepoint){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Grade Point:</td><td>".$row->gradepoint."</td></tr>";
	}
	if($row->dropped){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Dropped:</td><td>".$row->dropped."</td></tr>";
	}
	if($row->creditload){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Credit Load:</td><td>".$row->creditload."</td></tr>";
	}
	if($row->approved){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Approved:</td><td>".$row->approved."</td></tr>";
	}
	if($row->submitted){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Submitted:</td><td>".$row->submitted."</td></tr>";
	}
	if($row->submittedby){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Submitted By:</td><td>".$row->submittedby."</td></tr>";
	}
	$output.= '</table>';
	
 return $output;
}
