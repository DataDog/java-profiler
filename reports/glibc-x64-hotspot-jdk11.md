---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 06:37:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 51-78 cores)</summary>

```
1795519967 78
1795519972 78
1795519977 78
1795519982 78
1795519987 78
1795519992 78
1795519997 78
1795520002 78
1795520007 78
1795520012 78
1795520017 78
1795520022 69
1795520027 69
1795520032 69
1795520037 69
1795520042 69
1795520047 69
1795520052 69
1795520057 69
1795520062 69
```
</details>

---

