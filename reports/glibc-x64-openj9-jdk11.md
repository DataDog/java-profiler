---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:01:30 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1794585405 91
1794585410 91
1794585415 91
1794585420 91
1794585425 91
1794585430 91
1794585435 91
1794585440 91
1794585445 91
1794585450 91
1794585455 91
1794585460 94
1794585465 94
1794585470 94
1794585475 94
1794585480 94
1794585485 94
1794585490 94
1794585495 94
1794585500 94
```
</details>

---

