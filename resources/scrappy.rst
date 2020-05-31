      #   - run:
      #       name: checks $CPATH envar after source
      #       command: echo $CPATH
      #   - run:
      #       name: builds and tests the return-string project
      #       command: "cd projects/return-string/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh"
      #   - run:
      #       name: builds and tests the showdate project
      #       command: "cd projects/showdate/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh"

            #   - run:
      #       name: builds and tests the return-string project
      #       command: "cd projects/return-string/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh"
      #   - run:
      #       name: check what os we got and run platform dependent script
      #       command: cd projects/showdate/ && chmod 775 check_os.sh && ./check_os.sh
      #   - run:
      #       name: builds and tests array_generator project
      #       command: "cd projects/array-create/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh"

            #   - run:
      #       name: builds and tests the return-string project
      #       command: cd projects/return-string/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh
      #   - run:
      #       name: builds and tests the showdate project
      #       command: cd projects/showdate/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh
      #   - run:
      #       name: builds and tests array_generator project
      #       command: "cd projects/array-create/ && chmod 775 check_os.sh && chmod 775 wipebuild.sh && ./check_os.sh"