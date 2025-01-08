;;;; turtle.asd

(asdf:defsystem #:turtle
  :description "turtle shell"
  :author "George Watson <gigolo@hotmail.co.uk>"
  :license  "GPL-3.0"
  :version "0.0.1"
  :serial t
  :components ((:file "package")
               (:file "turtle")))
