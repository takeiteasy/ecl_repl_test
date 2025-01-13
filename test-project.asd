;;;; project.asd

(asdf:defsystem #:test-project
  :description "test"
  :author "George Watson <gigolo@hotmail.co.uk>"
  :license  "GPL-3.0"
  :version "0.0.1"
  :serial t
  :components ((:file "package")
               (:file "test")))
