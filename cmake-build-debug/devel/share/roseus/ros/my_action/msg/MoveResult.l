;; Auto-generated. Do not edit!


(when (boundp 'my_action::MoveResult)
  (if (not (find-package "MY_ACTION"))
    (make-package "MY_ACTION"))
  (shadow 'MoveResult (find-package "MY_ACTION")))
(unless (find-package "MY_ACTION::MOVERESULT")
  (make-package "MY_ACTION::MOVERESULT"))

(in-package "ROS")
;;//! \htmlinclude MoveResult.msg.html


(defclass my_action::MoveResult
  :super ros::object
  :slots (_res ))

(defmethod my_action::MoveResult
  (:init
   (&key
    ((:res __res) "")
    )
   (send-super :init)
   (setq _res (string __res))
   self)
  (:res
   (&optional __res)
   (if __res (setq _res __res)) _res)
  (:serialization-length
   ()
   (+
    ;; string _res
    4 (length _res)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _res
       (write-long (length _res) s) (princ _res s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _res
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _res (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get my_action::MoveResult :md5sum-) "53af918a2a4a2a182c184142fff49b0c")
(setf (get my_action::MoveResult :datatype-) "my_action/MoveResult")
(setf (get my_action::MoveResult :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#result definition
string res

")



(provide :my_action/MoveResult "53af918a2a4a2a182c184142fff49b0c")


