; Auto-generated. Do not edit!


(cl:in-package my_action-msg)


;//! \htmlinclude MoveGoal.msg.html

(cl:defclass <MoveGoal> (roslisp-msg-protocol:ros-message)
  ((location_name
    :reader location_name
    :initarg :location_name
    :type cl:string
    :initform ""))
)

(cl:defclass MoveGoal (<MoveGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_action-msg:<MoveGoal> is deprecated: use my_action-msg:MoveGoal instead.")))

(cl:ensure-generic-function 'location_name-val :lambda-list '(m))
(cl:defmethod location_name-val ((m <MoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_action-msg:location_name-val is deprecated.  Use my_action-msg:location_name instead.")
  (location_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveGoal>) ostream)
  "Serializes a message object of type '<MoveGoal>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'location_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'location_name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveGoal>) istream)
  "Deserializes a message object of type '<MoveGoal>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'location_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'location_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveGoal>)))
  "Returns string type for a message object of type '<MoveGoal>"
  "my_action/MoveGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveGoal)))
  "Returns string type for a message object of type 'MoveGoal"
  "my_action/MoveGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveGoal>)))
  "Returns md5sum for a message object of type '<MoveGoal>"
  "73faf335e0992a31df2e9630ffb73b0b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveGoal)))
  "Returns md5sum for a message object of type 'MoveGoal"
  "73faf335e0992a31df2e9630ffb73b0b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveGoal>)))
  "Returns full string definition for message of type '<MoveGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%string location_name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveGoal)))
  "Returns full string definition for message of type 'MoveGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%string location_name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveGoal>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'location_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveGoal
    (cl:cons ':location_name (location_name msg))
))
