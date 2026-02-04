---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-04 10:23:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 13 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1770218193 77
1770218198 77
1770218203 77
1770218208 77
1770218213 77
1770218218 77
1770218223 77
1770218228 77
1770218233 77
1770218238 77
1770218243 77
1770218248 77
1770218253 77
1770218258 77
1770218263 77
1770218268 81
1770218273 81
1770218278 81
1770218283 81
1770218288 81
```
</details>

---

