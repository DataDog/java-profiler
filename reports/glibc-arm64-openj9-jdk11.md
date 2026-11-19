---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 00:05:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1795064478 44
1795064483 44
1795064488 44
1795064493 44
1795064498 44
1795064503 44
1795064508 44
1795064513 44
1795064518 44
1795064523 44
1795064528 44
1795064533 44
1795064538 44
1795064543 44
1795064548 44
1795064553 44
1795064558 44
1795064563 44
1795064568 64
1795064573 64
```
</details>

---

