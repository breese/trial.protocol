add_custom_target(doc-protocol ALL
    COMMAND asciidoctor -b html -D html ${CMAKE_CURRENT_SOURCE_DIR}/protocol/protocol.adoc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/protocol)

add_custom_target(doc-dynamic ALL
    COMMAND asciidoctor -b html -D html ${CMAKE_CURRENT_SOURCE_DIR}/dynamic/dynamic.adoc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dynamic)
