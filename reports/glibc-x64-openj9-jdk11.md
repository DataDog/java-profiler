---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:10:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 58-78 cores)</summary>

```
1795107955 71
1795107960 71
1795107965 71
1795107970 71
1795107975 71
1795107980 71
1795107985 71
1795107990 71
1795107995 69
1795108000 69
1795108005 69
1795108010 69
1795108015 69
1795108020 69
1795108025 69
1795108030 69
1795108035 69
1795108040 69
1795108045 69
1795108050 69
```
</details>

---

