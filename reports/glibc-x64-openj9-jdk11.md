---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 12:17:40 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1787242455 94
1787242460 94
1787242465 94
1787242470 92
1787242475 92
1787242480 92
1787242485 94
1787242490 94
1787242495 94
1787242500 94
1787242505 92
1787242510 92
1787242515 92
1787242520 92
1787242525 90
1787242530 90
1787242535 92
1787242540 92
1787242545 92
1787242550 92
```
</details>

---

