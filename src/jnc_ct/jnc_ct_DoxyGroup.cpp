#include "pch.h"
#include "jnc_ct_DoxyGroup.h"
#include "jnc_ct_Module.h"

namespace jnc {
namespace ct {

//.............................................................................

bool
DoxyGroup::generateDocumentation (
	const char* outputDir,
	sl::String* itemXml,
	sl::String* indexXml
	)
{
	indexXml->appendFormat (
		"<compound kind='group' refid='%s'><name>%s</name></compound>\n", 
		m_refId.cc (), 
		m_name.cc ()
		);

	itemXml->format (
		"<compounddef kind='group' id='%s'>\n"
		"<compoundname>%s</compoundname>\n"
		"<title>%s</title>\n", 
		m_refId.cc (), 
		m_name.cc (),
		m_title.cc ()
		);

	sl::String sectionDef;

	size_t count = m_itemArray.getCount ();
	for (size_t i = 0; i < count; i++)
	{
		ModuleItem* item = m_itemArray [i];
		ModuleItemDecl* decl = item->getDecl ();
		if (!decl)
			continue;

		ModuleItemKind itemKind = item->getItemKind ();

		bool isCompoundFile = 
			itemKind == ModuleItemKind_Namespace ||
			itemKind == ModuleItemKind_Type && ((Type*) item)->getTypeKind () != TypeKind_Enum;

		sl::String refId = item->getDoxyBlock ()->getRefId ();

		if (!isCompoundFile)
		{
			sectionDef.appendFormat ("<memberdef id='%s'/>", refId.cc ());
			sectionDef.append ('\n');
		}
		else
		{
			const char* elemName = itemKind == ModuleItemKind_Namespace ? "innernamespace" : "innerclass";
			sl::String refId = item->getDoxyBlock ()->getRefId ();
			itemXml->appendFormat ("<%s refid='%s'/>", elemName, refId.cc ());
			itemXml->append ('\n');
		}
	}

	if (!sectionDef.isEmpty ())
	{
		itemXml->append ("<sectiondef>\n");
		itemXml->append (sectionDef);
		itemXml->append ("</sectiondef>\n");
	}

	sl::BoxIterator <DoxyGroup*> groupIt = m_groupList.getHead ();
	for (; groupIt; groupIt++)
	{
		DoxyGroup* group = *groupIt;
		itemXml->appendFormat ("<innergroup refid='%s'/>", group->m_refId.cc ());
		itemXml->append ('\n');
	}

	itemXml->append (createDescriptionString ());
	itemXml->append ("</compounddef>\n");

	return true;
}

//.............................................................................

} // namespace ct
} // namespace jnc