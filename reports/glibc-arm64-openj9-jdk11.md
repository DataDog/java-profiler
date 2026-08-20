---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 13:25:44 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 10 |
| Allocations | 203 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 17-22 cores)</summary>

```
1787246465 17
1787246470 17
1787246475 17
1787246480 17
1787246485 17
1787246490 17
1787246495 17
1787246500 22
1787246505 22
1787246510 22
1787246515 22
1787246520 22
1787246525 22
1787246530 22
1787246535 22
1787246540 22
1787246545 22
1787246550 22
1787246555 22
1787246560 22
```
</details>

---

