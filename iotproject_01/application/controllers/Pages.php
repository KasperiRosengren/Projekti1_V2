<?php
	class Pages extends CI_CONTROLLER
	{

		function __construct()
		{
			parent::__construct();
		}

		public function view($page = 'home')
		{
			if(!file_exists(APPPATH.'views/pages/'.$page.'.php'))
			{
				show_404();
			}
			$this->load->library('session');
			$this->load->database();
			$data['title'] = ucfirst($page);
			$this->load->view('templates/header');
			$this->load->view('pages/'.$page, $data);
			$this->load->view('templates/footer');
		}

		public function login_user(){
            $username = $this->input->post("username");
            $password = $this->input->post("password");

			try {
				$this-> db->select('idLoginUsers');
		        $this-> db->from('LoginUsers');
		        $this-> db->where('USERNAME', $username);
		        $this-> db->where('PASSWORD', $password);
		        $this-> db->limit(1);
		        $query = $this-> db->get();

		        if ($query->num_rows() == 1)
		        {   

		        	foreach ($query->result() as $row)
					{
					     $this->session->userID = $row->idLoginUsers;
					}
		        	redirect('/user');
		        }
		        else
		        {
		            echo 'Invalid username or password';
		            return (FALSE);
		        }
	
			} catch (Exception $e) {
				echo $e->getMessage();
			}
        }

        public function logout_user(){
        	$this->session->userID = 0;
        	redirect('/user');
        }

        public function open_door(){
        	$deviceid = $this->input->post("deviceid");
        	if (is_numeric($deviceid)) {
	        	$query="insert into Tila(Laite_idLaite, Tila) values('$deviceid','1')";
				$this->db->query($query);
	        	sleep(1);
	        	$rquery="insert into Tila(Laite_idLaite, Tila) values('$deviceid','0')";
	        	$this->db->query($rquery);

        	}
        	else{
        		$msg = "Not a number";
        		$this->session->set_flashdata('userdata', $msg);
        	}
        	
        	redirect('/devices');
        }

        public function testform(){
        	$value1 = $this->input->post("input");
        	$datatype = $this->input->post("type");

        	if ($datatype=='user') 
        	{
        		$name = explode(',', $value1);
        		$value1 = $name[0];
        		$value2 = $name[1];

        		$output = array('value1'=>$value1, 'value2'=>$value2,'datatype'=>$datatype);
	        	$this->session->set_flashdata('userdata', $output);
        	}
        	elseif ($datatype=='UID') {
        		$output = array('value1'=>$value1,'datatype'=>$datatype);
	        	$this->session->set_flashdata('userdata', $output);
        	}
	        redirect('/data');

        }
	}