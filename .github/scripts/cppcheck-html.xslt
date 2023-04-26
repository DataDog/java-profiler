<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns="http://www.w3.org/1999/xhtml">

    <xsl:output method="html"/>

    <xsl:param name="target_branch" select="'main'"/>

    <xsl:key name="errorById" match="error" use="@id"/>

    <xsl:template match="/">
        <html>
            <head>
                <title>Results</title>
                <style>
                    body {
                    font-family: Arial, sans-serif;
                    font-size: 14px;
                    color: #333;
                    }
                </style>
            </head>
            <body>
                <h1>CppCheck Report</h1>
                <h2>Errors</h2>
                <ul>
                <xsl:for-each select="results/errors/error[@severity = 'error']">
                    <xsl:variable name="source">
                        <xsl:value-of select="concat(location/@file, '#L', location/@line)"/>
                    </xsl:variable>
                    <li>
                        <a href="https://github.com/DataDog/java-profiler-library/blob/target_branch/{$source}">
                            <xsl:value-of select="@msg"/>
                        </a>
                    </li>
                </xsl:for-each>
                </ul>
                <hr/>
                <h2>Warnings</h2>
                <ul>
                <xsl:for-each select="results/errors/error[@severity = 'warning']">
                    <xsl:variable name="source">
                        <xsl:value-of select="concat(location/@file, '#L', location/@line)"/>
                    </xsl:variable>
                    <li>
                        <a href="https://github.com/DataDog/java-profiler-library/blob/target_branch/{$source}">
                            <xsl:value-of select="@msg"/>
                        </a>
                    </li>
                </xsl:for-each>
                </ul>
                <!-- Temporarily disable very noisy style violations - until we get a collapsing HTML -->
<!--                <hr/>-->
<!--                <h2>Style Violations</h2>-->
<!--                <ul>-->
<!--                <xsl:for-each select="results/errors/error[@severity = 'style']">-->
<!--                    <xsl:variable name="source">-->
<!--                        <xsl:value-of select="concat(location/@file, '#L', location/@line)"/>-->
<!--                    </xsl:variable>-->
<!--                    <li>-->
<!--                        <a href="https://github.com/DataDog/java-profiler-library/blob/target_branch/{$source}">-->
<!--                            <xsl:value-of select="@msg"/>-->
<!--                        </a>-->
<!--                    </li>-->
<!--                </xsl:for-each>-->
<!--                </ul>-->
            </body>
        </html>
    </xsl:template>

    <xsl:template match="error">
        <xsl:variable name="source">
            <xsl:value-of select="concat(location/@file, '#L', location/@line)"/>
        </xsl:variable>

        <tr>
            <td>
                <div class="title"><xsl:value-of select="@msg"/></div>
                <a href="https://github.com/DataDog/java-profiler-library/blob/target_branch/{$source}">
                    <xsl:value-of select="$source"/>
                </a>
            </td>
        </tr>
    </xsl:template>

</xsl:stylesheet>
