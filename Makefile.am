ACLOCAL_AMFLAGS = -I build-aux/m4
SUBDIRS = src
.PHONY: deploy FORCE

GZIP_ENV="-9n"

q3chainD_BIN=$(top_builddir)/src/q3chaind$(EXEEXT)
q3chain_QT_BIN=$(top_builddir)/src/qt/q3chain-qt$(EXEEXT)
q3chain_CLI_BIN=$(top_builddir)/src/q3chain-cli$(EXEEXT)
q3chain_WIN_INSTALLER=$(PACKAGE)-$(PACKAGE_VERSION)-win$(WINDOWS_BITS)-setup$(EXEEXT)

# MCHN START

q3chainD_BIN=$(top_builddir)/src/q3chaind$(EXEEXT)
q3chainD_COLD_BIN=$(top_builddir)/src/q3chaind-cold$(EXEEXT)
q3chain_CLI_BIN=$(top_builddir)/src/q3chain-cli$(EXEEXT)
q3chain_UTIL_BIN=$(top_builddir)/src/q3chain-util$(EXEEXT)

# MCHN END

OSX_APP=q3chain-Qt.app
OSX_DMG=q3chain-Qt.dmg
OSX_DEPLOY_SCRIPT=$(top_srcdir)/contrib/macdeploy/macdeployqtplus
OSX_FANCY_PLIST=$(top_srcdir)/contrib/macdeploy/fancy.plist
OSX_INSTALLER_ICONS=$(top_srcdir)/src/qt/res/icons/q3chain.icns
OSX_PLIST=$(top_srcdir)/share/qt/Info.plist #not installed
OSX_QT_TRANSLATIONS = da,de,es,hu,ru,uk,zh_CN,zh_TW

DIST_DOCS = $(wildcard doc/*.md) $(wildcard doc/release-notes/*.md)

WINDOWS_PACKAGING = $(top_srcdir)/share/pixmaps/q3chain.ico \
  $(top_srcdir)/share/pixmaps/nsis-header.bmp \
  $(top_srcdir)/share/pixmaps/nsis-wizard.bmp \
  $(top_srcdir)/doc/README_windows.txt

OSX_PACKAGING = $(OSX_DEPLOY_SCRIPT) $(OSX_FANCY_PLIST) $(OSX_INSTALLER_ICONS) \
  $(top_srcdir)/contrib/macdeploy/background.png \
  $(top_srcdir)/contrib/macdeploy/DS_Store \
  $(top_srcdir)/contrib/macdeploy/detached-sig-apply.sh \
  $(top_srcdir)/contrib/macdeploy/detached-sig-create.sh

COVERAGE_INFO = baseline_filtered_combined.info baseline.info block_test.info \
  leveldb_baseline.info test_q3chain_filtered.info total_coverage.info \
  baseline_filtered.info block_test_filtered.info \
  leveldb_baseline_filtered.info test_q3chain_coverage.info test_q3chain.info

dist-hook:
	-$(MAKE) -C $(top_distdir)/src/leveldb clean
	-$(MAKE) -C $(top_distdir)/src/secp256k1 distclean
	-$(GIT) archive --format=tar HEAD -- src/clientversion.cpp | $(AMTAR) -C $(top_distdir) -xf -

distcheck-hook:
	$(MKDIR_P) $(top_distdir)/_build/src/leveldb
	cp -rf $(top_srcdir)/src/leveldb/* $(top_distdir)/_build/src/leveldb/
	-$(MAKE) -C $(top_distdir)/_build/src/leveldb clean

distcleancheck:
	@:

$(q3chain_WIN_INSTALLER): all-recursive
	$(MKDIR_P) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(q3chainD_BIN) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(q3chain_QT_BIN) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(q3chain_CLI_BIN) $(top_builddir)/release
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(q3chainD_BIN) $(top_builddir)/release    # MCHN
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(q3chainD_COLD_BIN) $(top_builddir)/release    # MCHN
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(MULTICHAI_CLI_BIN) $(top_builddir)/release  # MCHN
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM) $(MULTICHAI_UTIL_BIN) $(top_builddir)/release # MCHN
	@test -f $(MAKENSIS) && $(MAKENSIS) $(top_builddir)/share/setup.nsi || \
	  echo error: could not build $@

$(if $(findstring src/,$(MAKECMDGOALS)),$(MAKECMDGOALS), none): FORCE
	$(MAKE) -C src $(patsubst src/%,%,$@)

$(OSX_APP)/Contents/PkgInfo:
	$(MKDIR_P) $(@D)
	@echo "APPL????" > $@

$(OSX_APP)/Contents/Resources/empty.lproj:
	$(MKDIR_P) $(@D)
	@touch $@

$(OSX_APP)/Contents/Info.plist: $(OSX_PLIST)
	$(MKDIR_P) $(@D)
	$(INSTALL_DATA) $< $@

$(OSX_APP)/Contents/Resources/q3chain.icns: $(OSX_INSTALLER_ICONS)
	$(MKDIR_P) $(@D)
	$(INSTALL_DATA) $< $@

$(OSX_APP)/Contents/MacOS/q3chain-Qt: $(q3chain_QT_BIN)
	$(MKDIR_P) $(@D)
	STRIPPROG="$(STRIP)" $(INSTALL_STRIP_PROGRAM)  $< $@

OSX_APP_BUILT=$(OSX_APP)/Contents/PkgInfo $(OSX_APP)/Contents/Resources/empty.lproj \
  $(OSX_APP)/Contents/Resources/q3chain.icns $(OSX_APP)/Contents/Info.plist \
  $(OSX_APP)/Contents/MacOS/q3chain-Qt

if BUILD_DARWIN
$(OSX_DMG): $(OSX_APP_BUILT) $(OSX_PACKAGING)
	$(OSX_DEPLOY_SCRIPT) $(OSX_APP) -add-qt-tr $(OSX_QT_TRANSLATIONS) -translations-dir=$(QT_TRANSLATION_DIR) -dmg -fancy $(OSX_FANCY_PLIST) -verbose 2

deploydir: $(OSX_DMG)
else
APP_DIST_DIR=$(top_builddir)/dist
APP_DIST_EXTRAS=$(APP_DIST_DIR)/.background/background.png $(APP_DIST_DIR)/.DS_Store $(APP_DIST_DIR)/Applications

$(APP_DIST_DIR)/Applications:
	@rm -f $@
	@cd $(@D); $(LN_S) /Applications $(@F)

$(APP_DIST_EXTRAS): $(APP_DIST_DIR)/$(OSX_APP)/Contents/MacOS/q3chain-Qt

$(OSX_DMG): $(APP_DIST_EXTRAS)
	$(GENISOIMAGE) -no-cache-inodes -D -l -probe -V "q3chain-Qt" -no-pad -r -apple -o $@ dist

$(APP_DIST_DIR)/.background/background.png:
	$(MKDIR_P) $(@D)
	$(INSTALL) $(top_srcdir)/contrib/macdeploy/background.png $@
$(APP_DIST_DIR)/.DS_Store:
	$(INSTALL) $(top_srcdir)/contrib/macdeploy/DS_Store $@

$(APP_DIST_DIR)/$(OSX_APP)/Contents/MacOS/q3chain-Qt: $(OSX_APP_BUILT) $(OSX_PACKAGING)
	INSTALLNAMETOOL=$(INSTALLNAMETOOL)  OTOOL=$(OTOOL) STRIP=$(STRIP) $(OSX_DEPLOY_SCRIPT) $(OSX_APP) -translations-dir=$(QT_TRANSLATION_DIR) -add-qt-tr $(OSX_QT_TRANSLATIONS) -verbose 2

deploydir: $(APP_DIST_EXTRAS)
endif

if TARGET_DARWIN
appbundle: $(OSX_APP_BUILT)
deploy: $(OSX_DMG)
endif
if TARGET_WINDOWS
deploy: $(q3chain_WIN_INSTALLER)
endif

$(q3chain_QT_BIN): FORCE
	$(MAKE) -C src qt/$(@F)

$(q3chainD_BIN): FORCE
	$(MAKE) -C src $(@F)

$(q3chain_CLI_BIN): FORCE
	$(MAKE) -C src $(@F)

# MCHN START

$(q3chainD_BIN): FORCE
	$(MAKE) -C src $(@F)

$(q3chainD_COLD_BIN): FORCE
	$(MAKE) -C src $(@F)

$(q3chain_CLI_BIN): FORCE
	$(MAKE) -C src $(@F)

$(q3chain_UTIL_BIN): FORCE
	$(MAKE) -C src $(@F)

# MCHN END

if USE_LCOV

baseline.info:
	$(LCOV) -c -i -d $(abs_builddir)/src -o $@

baseline_filtered.info: baseline.info
	$(LCOV) -r $< "/usr/include/*" -o $@

leveldb_baseline.info: baseline_filtered.info
	$(LCOV) -c -i -d $(abs_builddir)/src/leveldb -b $(abs_builddir)/src/leveldb -o $@

leveldb_baseline_filtered.info: leveldb_baseline.info
	$(LCOV) -r $< "/usr/include/*" -o $@

baseline_filtered_combined.info: leveldb_baseline_filtered.info baseline_filtered.info
	$(LCOV) -a leveldb_baseline_filtered.info -a baseline_filtered.info -o $@

test_q3chain.info: baseline_filtered_combined.info
	$(MAKE) -C src/ check
	$(LCOV) -c -d $(abs_builddir)/src -t test_q3chain -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

test_q3chain_filtered.info: test_q3chain.info
	$(LCOV) -r $< "/usr/include/*" -o $@

block_test.info: test_q3chain_filtered.info
	$(MKDIR_P) qa/tmp
	-@TIMEOUT=15 qa/pull-tester/run-q3chaind-for-test.sh $(JAVA) -jar $(JAVA_COMPARISON_TOOL) qa/tmp/compTool 0
	$(LCOV) -c -d $(abs_builddir)/src --t q3chainJBlockTest -o $@
	$(LCOV) -z -d $(abs_builddir)/src
	$(LCOV) -z -d $(abs_builddir)/src/leveldb

block_test_filtered.info: block_test.info
	$(LCOV) -r $< "/usr/include/*" -o $@

test_q3chain_coverage.info: baseline_filtered_combined.info test_q3chain_filtered.info
	$(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_q3chain_filtered.info -o $@

total_coverage.info:  baseline_filtered_combined.info test_q3chain_filtered.info block_test_filtered.info
	$(LCOV) -a baseline_filtered.info -a leveldb_baseline_filtered.info -a test_q3chain_filtered.info -a block_test_filtered.info -o $@ | $(GREP) "\%" | $(AWK) '{ print substr($$3,2,50) "/" $$5 }' > coverage_percent.txt

test_q3chain.coverage/.dirstamp:  test_q3chain_coverage.info
	$(GENHTML) -s $< -o $(@D)
	@touch $@

total.coverage/.dirstamp: total_coverage.info
	$(GENHTML) -s $< -o $(@D)
	@touch $@

cov: test_q3chain.coverage/.dirstamp total.coverage/.dirstamp

endif

if USE_COMPARISON_TOOL
check-local:
	$(MKDIR_P) qa/tmp
	@qa/pull-tester/run-q3chaind-for-test.sh $(JAVA) -jar $(JAVA_COMPARISON_TOOL) qa/tmp/compTool $(COMPARISON_TOOL_REORG_TESTS) 2>&1
endif

EXTRA_DIST = $(top_srcdir)/share/genbuild.sh qa/pull-tester/rpc-tests.sh qa/pull-tester/run-q3chain-cli qa/rpc-tests $(DIST_DOCS) $(WINDOWS_PACKAGING) $(OSX_PACKAGING)

CLEANFILES = $(OSX_DMG) $(q3chain_WIN_INSTALLER)

.INTERMEDIATE: $(COVERAGE_INFO)

clean-local:
	rm -rf test_q3chain.coverage/ total.coverage/ $(OSX_APP)
