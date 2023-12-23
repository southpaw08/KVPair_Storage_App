KVPSTORAGE_VERSION = 1.0
KVPSTORAGE_SITE = ./package/KVPStorage/src
KVPSTORAGE_SITE_METHOD = local


define KVPSTORAGE_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" LD="$(TARGET_LD)" -C $(@D)
endef

define KVPSTORAGE_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/KVPStorage $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))
