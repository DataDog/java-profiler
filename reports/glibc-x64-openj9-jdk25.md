---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:10:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 72-93 cores)</summary>

```
1795107995 93
1795108000 93
1795108005 93
1795108010 93
1795108015 93
1795108020 93
1795108025 93
1795108030 93
1795108035 93
1795108040 93
1795108045 93
1795108050 93
1795108055 93
1795108060 93
1795108065 93
1795108070 93
1795108075 74
1795108080 74
1795108085 74
1795108090 74
```
</details>

---

