---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 12:32:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 77-88 cores)</summary>

```
1793031994 77
1793031999 77
1793032004 77
1793032009 77
1793032014 77
1793032019 77
1793032024 77
1793032029 77
1793032034 77
1793032039 77
1793032044 77
1793032049 77
1793032054 77
1793032059 77
1793032064 88
1793032069 88
1793032074 88
1793032079 86
1793032084 86
1793032089 86
```
</details>

---

