---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 69-81 cores)</summary>

```
1788547910 81
1788547915 81
1788547920 81
1788547925 69
1788547930 69
1788547935 69
1788547940 69
1788547945 69
1788547950 69
1788547955 69
1788547960 69
1788547965 69
1788547970 69
1788547975 69
1788547980 69
1788547985 69
1788547990 69
1788547995 69
1788548000 69
1788548005 69
```
</details>

---

