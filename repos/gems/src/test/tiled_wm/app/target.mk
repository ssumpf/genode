include $(call select_from_repositories,src/app/qt5/tmpl/target_defaults.inc)

include $(call select_from_repositories,src/app/qt5/tmpl/target_final.inc)

CC_CXX_WARN_STRICT =

INC_DIR += $(PRG_DIR)/..

#app.o: app.moc
