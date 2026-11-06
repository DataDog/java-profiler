/*
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.io.File;
import java.net.URL;
import java.util.jar.Attributes;
import java.util.jar.JarFile;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * The profiler jar's manifest identifies the build: its version and the commit it was built
 * from, since a snapshot version alone does not identify the source. The tests run against the
 * assembled jar of the tested configuration, so this reads the manifest of that jar.
 */
public class JarManifestTest {

  /** Title, vendor, version and commit are present, and the version matches the jar's name. */
  @Test
  public void manifestRecordsVersionAndCommit() throws Exception {
    URL location = JavaProfiler.class.getProtectionDomain().getCodeSource().getLocation();
    assertTrue(location.getPath().endsWith(".jar"), "profiler classes not loaded from a jar: " + location);
    try (JarFile jar = new JarFile(new File(location.toURI()))) {
      Attributes attributes = jar.getManifest().getMainAttributes();
      assertEquals("ddprof", attributes.getValue("Implementation-Title"));
      String version = attributes.getValue("Implementation-Version");
      assertNotNull(version, "no Implementation-Version in " + location);
      assertTrue(jar.getName().contains(version), "version " + version + " does not match " + jar.getName());
      assertEquals("Datadog", attributes.getValue("Implementation-Vendor"));
      String commit = attributes.getValue("Git-Commit");
      assertNotNull(commit, "no Git-Commit in " + location);
      String ciCommit = System.getenv("CI_COMMIT_SHA");
      if (ciCommit != null && !ciCommit.isEmpty()) {
        // GitLab, which publishes the jars: the commit must be the one CI built.
        assertEquals(ciCommit, commit);
      } else {
        // "unknown" only where the build could not run git.
        assertTrue(commit.matches("[0-9a-f]{40}") || commit.equals("unknown"), "malformed Git-Commit: " + commit);
      }
    }
  }
}
