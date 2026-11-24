---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 06:37:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 67-78 cores)</summary>

```
1795519962 78
1795519967 69
1795519972 69
1795519977 69
1795519982 69
1795519987 69
1795519992 69
1795519997 69
1795520002 69
1795520007 69
1795520012 69
1795520017 69
1795520022 69
1795520027 69
1795520032 69
1795520037 67
1795520042 67
1795520047 67
1795520052 67
1795520057 67
```
</details>

---

