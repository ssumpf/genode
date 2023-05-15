include $(call select_from_repositories,lib/import/import-icu.mk)

ICU_DIR := $(call select_from_ports,icu)/src/lib/icu

#
# Retrieved from $(ICU_DIR)/source/common/*.cpp an renamed to *.o
#
ICU_COMMON_OBJECTS = appendable.o \
                     bmpset.o \
                     brkeng.o \
                     brkiter.o \
                     bytesinkutil.o \
                     bytestream.o \
                     bytestriebuilder.o \
                     bytestrie.o \
                     bytestrieiterator.o \
                     caniter.o \
                     characterproperties.o \
                     chariter.o \
                     charstr.o \
                     cmemory.o \
                     cstr.o \
                     cstring.o \
                     cwchar.o \
                     dictbe.o \
                     dictionarydata.o \
                     dtintrv.o \
                     edits.o \
                     emojiprops.o \
                     errorcode.o \
                     filteredbrk.o \
                     filterednormalizer2.o \
                     icudataver.o \
                     icuplug.o \
                     loadednormalizer2impl.o \
                     localebuilder.o \
                     localematcher.o \
                     localeprioritylist.o \
                     locavailable.o \
                     locbased.o \
                     locdispnames.o \
                     locdistance.o \
                     locdspnm.o \
                     locid.o \
                     loclikely.o \
                     loclikelysubtags.o \
                     locmap.o \
                     locresdata.o \
                     locutil.o \
                     lsr.o \
                     lstmbe.o \
                     messagepattern.o \
                     mlbe.o \
                     normalizer2.o \
                     normalizer2impl.o \
                     normlzr.o \
                     parsepos.o \
                     patternprops.o \
                     pluralmap.o \
                     propname.o \
                     propsvec.o \
                     punycode.o \
                     putil.o \
                     rbbi_cache.o \
                     rbbi.o \
                     rbbidata.o \
                     rbbinode.o \
                     rbbirb.o \
                     rbbiscan.o \
                     rbbisetb.o \
                     rbbistbl.o \
                     rbbitblb.o \
                     resbund_cnv.o \
                     resbund.o \
                     resource.o \
                     restrace.o \
                     ruleiter.o \
                     schriter.o \
                     serv.o \
                     servlk.o \
                     servlkf.o \
                     servls.o \
                     servnotf.o \
                     servrbf.o \
                     servslkf.o \
                     sharedobject.o \
                     simpleformatter.o \
                     static_unicode_sets.o \
                     stringpiece.o \
                     stringtriebuilder.o \
                     uarrsort.o \
                     ubidi.o \
                     ubidiln.o \
                     ubidi_props.o \
                     ubiditransform.o \
                     ubidiwrt.o \
                     ubrk.o \
                     ucase.o \
                     ucasemap.o \
                     ucasemap_titlecase_brkiter.o \
                     ucat.o \
                     uchar.o \
                     ucharstriebuilder.o \
                     ucharstrie.o \
                     ucharstrieiterator.o \
                     uchriter.o \
                     ucln_cmn.o \
                     ucmndata.o \
                     ucnv2022.o \
                     ucnv_bld.o \
                     ucnvbocu.o \
                     ucnv_cb.o \
                     ucnv_cnv.o \
                     ucnv.o \
                     ucnv_ct.o \
                     ucnvdisp.o \
                     ucnv_err.o \
                     ucnv_ext.o \
                     ucnvhz.o \
                     ucnv_io.o \
                     ucnvisci.o \
                     ucnvlat1.o \
                     ucnv_lmb.o \
                     ucnvmbcs.o \
                     ucnvscsu.o \
                     ucnvsel.o \
                     ucnv_set.o \
                     ucnv_u16.o \
                     ucnv_u32.o \
                     ucnv_u7.o \
                     ucnv_u8.o \
                     ucol_swp.o \
                     ucptrie.o \
                     ucurr.o \
                     udata.o \
                     udatamem.o \
                     udataswp.o \
                     uenum.o \
                     uhash.o \
                     uhash_us.o \
                     uidna.o \
                     uinit.o \
                     uinvchar.o \
                     uiter.o \
                     ulist.o \
                     uloc.o \
                     uloc_keytype.o \
                     uloc_tag.o \
                     umapfile.o \
                     umath.o \
                     umutablecptrie.o \
                     umutex.o \
                     unames.o \
                     unifiedcache.o \
                     unifilt.o \
                     unifunct.o \
                     uniset_closure.o \
                     uniset.o \
                     uniset_props.o \
                     unisetspan.o \
                     unistr_case.o \
                     unistr_case_locale.o \
                     unistr_cnv.o \
                     unistr.o \
                     unistr_props.o \
                     unistr_titlecase_brkiter.o \
                     unormcmp.o \
                     unorm.o \
                     uobject.o \
                     uprops.o \
                     uresbund.o \
                     ures_cnv.o \
                     uresdata.o \
                     usc_impl.o \
                     uscript.o \
                     uscript_props.o \
                     uset.o \
                     usetiter.o \
                     uset_props.o \
                     ushape.o \
                     usprep.o \
                     ustack.o \
                     ustrcase.o \
                     ustrcase_locale.o \
                     ustr_cnv.o \
                     ustrenum.o \
                     ustrfmt.o \
                     ustring.o \
                     ustr_titlecase_brkiter.o \
                     ustrtrns.o \
                     ustr_wcs.o \
                     utext.o \
                     utf_impl.o \
                     util.o \
                     util_props.o \
                     utrace.o \
                     utrie2_builder.o \
                     utrie2.o \
                     utrie.o \
                     utrie_swap.o \
                     uts46.o \
                     utypes.o \
                     uvector.o \
                     uvectr32.o \
                     uvectr64.o \
                     wintz.o


SRC_C += $(filter $(ICU_COMMON_OBJECTS:.o=.c), $(notdir $(wildcard $(ICU_DIR)/source/common/*.c)))
SRC_C += $(filter $(ICU_I18N_OBJECTS:.o=.c), $(notdir $(wildcard $(ICU_DIR)/source/i18n/*.c)))

#
# Retrieved from $(ICU_DIR)/source/i18n/*.cpp and renamed *.o
#
ICU_I18N_OBJECTS = alphaindex.o \
                   anytrans.o \
                   astro.o \
                   basictz.o \
                   bocsu.o \
                   brktrans.o \
                   buddhcal.o \
                   calendar.o \
                   casetrn.o \
                   cecal.o \
                   chnsecal.o \
                   choicfmt.o \
                   coleitr.o \
                   collationbuilder.o \
                   collationcompare.o \
                   collation.o \
                   collationdatabuilder.o \
                   collationdata.o \
                   collationdatareader.o \
                   collationdatawriter.o \
                   collationfastlatinbuilder.o \
                   collationfastlatin.o \
                   collationfcd.o \
                   collationiterator.o \
                   collationkeys.o \
                   collationroot.o \
                   collationrootelements.o \
                   collationruleparser.o \
                   collationsets.o \
                   collationsettings.o \
                   collationtailoring.o \
                   collationweights.o \
                   coll.o \
                   compactdecimalformat.o \
                   coptccal.o \
                   cpdtrans.o \
                   csdetect.o \
                   csmatch.o \
                   csr2022.o \
                   csrecog.o \
                   csrmbcs.o \
                   csrsbcs.o \
                   csrucode.o \
                   csrutf8.o \
                   curramt.o \
                   currfmt.o \
                   currpinf.o \
                   currunit.o \
                   dangical.o \
                   datefmt.o \
                   dayperiodrules.o \
                   dcfmtsym.o \
                   decContext.o \
                   decimfmt.o \
                   decNumber.o \
                   displayoptions.o \
                   double-conversion-bignum.o \
                   double-conversion-bignum-dtoa.o \
                   double-conversion-cached-powers.o \
                   double-conversion-double-to-string.o \
                   double-conversion-fast-dtoa.o \
                   double-conversion-string-to-double.o \
                   double-conversion-strtod.o \
                   dtfmtsym.o \
                   dtitvfmt.o \
                   dtitvinf.o \
                   dtptngen.o \
                   dtrule.o \
                   erarules.o \
                   esctrn.o \
                   ethpccal.o \
                   fmtable_cnv.o \
                   fmtable.o \
                   format.o \
                   formatted_string_builder.o \
                   formattedval_iterimpl.o \
                   formattedval_sbimpl.o \
                   formattedvalue.o \
                   fphdlimp.o \
                   fpositer.o \
                   funcrepl.o \
                   gender.o \
                   gregocal.o \
                   gregoimp.o \
                   hebrwcal.o \
                   indiancal.o \
                   inputext.o \
                   islamcal.o \
                   iso8601cal.o \
                   japancal.o \
                   listformatter.o \
                   measfmt.o \
                   measunit.o \
                   measunit_extra.o \
                   measure.o \
                   msgfmt.o \
                   name2uni.o \
                   nfrs.o \
                   nfrule.o \
                   nfsubs.o \
                   nortrans.o \
                   nultrans.o \
                   number_affixutils.o \
                   number_asformat.o \
                   number_capi.o \
                   number_compact.o \
                   number_currencysymbols.o \
                   number_decimalquantity.o \
                   number_decimfmtprops.o \
                   number_fluent.o \
                   number_formatimpl.o \
                   number_grouping.o \
                   number_integerwidth.o \
                   number_longnames.o \
                   number_mapper.o \
                   number_modifiers.o \
                   number_multiplier.o \
                   number_notation.o \
                   number_output.o \
                   number_padding.o \
                   number_patternmodifier.o \
                   number_patternstring.o \
                   number_rounding.o \
                   number_scientific.o \
                   number_simple.o \
                   number_skeletons.o \
                   number_symbolswrapper.o \
                   number_usageprefs.o \
                   number_utils.o \
                   numfmt.o \
                   numparse_affixes.o \
                   numparse_compositions.o \
                   numparse_currency.o \
                   numparse_decimal.o \
                   numparse_impl.o \
                   numparse_parsednumber.o \
                   numparse_scientific.o \
                   numparse_symbols.o \
                   numparse_validators.o \
                   numrange_capi.o \
                   numrange_fluent.o \
                   numrange_impl.o \
                   numsys.o \
                   olsontz.o \
                   persncal.o \
                   pluralranges.o \
                   plurfmt.o \
                   plurrule.o \
                   quant.o \
                   quantityformatter.o \
                   rbnf.o \
                   rbt.o \
                   rbt_data.o \
                   rbt_pars.o \
                   rbt_rule.o \
                   rbt_set.o \
                   rbtz.o \
                   regexcmp.o \
                   regeximp.o \
                   regexst.o \
                   regextxt.o \
                   region.o \
                   reldatefmt.o \
                   reldtfmt.o \
                   rematch.o \
                   remtrans.o \
                   repattrn.o \
                   rulebasedcollator.o \
                   scientificnumberformatter.o \
                   scriptset.o \
                   search.o \
                   selfmt.o \
                   sharedbreakiterator.o \
                   simpletz.o \
                   smpdtfmt.o \
                   smpdtfst.o \
                   sortkey.o \
                   standardplural.o \
                   string_segment.o \
                   strmatch.o \
                   strrepl.o \
                   stsearch.o \
                   taiwncal.o \
                   timezone.o \
                   titletrn.o \
                   tmunit.o \
                   tmutamt.o \
                   tmutfmt.o \
                   tolowtrn.o \
                   toupptrn.o \
                   translit.o \
                   transreg.o \
                   tridpars.o \
                   tzfmt.o \
                   tzgnames.o \
                   tznames.o \
                   tznames_impl.o \
                   tzrule.o \
                   tztrans.o \
                   ucal.o \
                   ucln_in.o \
                   ucol.o \
                   ucoleitr.o \
                   ucol_res.o \
                   ucol_sit.o \
                   ucsdet.o \
                   udat.o \
                   udateintervalformat.o \
                   udatpg.o \
                   ufieldpositer.o \
                   uitercollationiterator.o \
                   ulistformatter.o \
                   ulocdata.o \
                   umsg.o \
                   unesctrn.o \
                   uni2name.o \
                   units_complexconverter.o \
                   units_converter.o \
                   units_data.o \
                   units_router.o \
                   unum.o \
                   unumsys.o \
                   upluralrules.o \
                   uregexc.o \
                   uregex.o \
                   uregion.o \
                   usearch.o \
                   uspoof_build.o \
                   uspoof_conf.o \
                   uspoof.o \
                   uspoof_impl.o \
                   utf16collationiterator.o \
                   utf8collationiterator.o \
                   utmscale.o \
                   utrans.o \
                   vtzone.o \
                   vzone.o \
                   windtfmt.o \
                   winnmfmt.o \
                   wintzimpl.o \
                   zonemeta.o \
                   zrule.o \
                   ztrans.o


SRC_CC += $(filter $(ICU_COMMON_OBJECTS:.o=.cpp), $(notdir $(wildcard $(ICU_DIR)/source/common/*.cpp)))
SRC_CC += $(filter $(ICU_I18N_OBJECTS:.o=.cpp), $(notdir $(wildcard $(ICU_DIR)/source/i18n/*.cpp)))


# provide the binary file 'icudt**l.dat' as symbol 'icud**_dat'
ICU_DAT             = icudt73l.dat
ICU_DAT_SYMBOL_NAME = icudt73_dat

SRC_BIN += $(ICU_DAT)

binary_$(ICU_DAT).o : $(ICU_DAT)
	$(MSG_CONVERT)$@
	$(VERBOSE)echo ".global $(ICU_DAT_SYMBOL_NAME); .section .rodata; .align 4; $(ICU_DAT_SYMBOL_NAME):; .incbin \"$<\"" |\
	          $(AS) $(AS_OPT) -f -o $@ -


CC_OPT += -DU_COMMON_IMPLEMENTATION -DU_I18N_IMPLEMENTATION

# prevent redefinition of the 'uintptr_t' type
CC_OPT += -D__intptr_t_defined

CC_WARN += -Wno-deprecated-declarations

LIBS = stdcxx

vpath % $(ICU_DIR)/source/common
vpath % $(ICU_DIR)/source/i18n
vpath % $(ICU_DIR)/source/data/in

SHARED_LIB = yes

CC_CXX_WARN_STRICT =
