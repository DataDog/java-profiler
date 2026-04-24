---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 11-44 cores)</summary>

```
1777064454 11
1777064460 11
1777064465 12
1777064470 12
1777064475 12
1777064480 12
1777064485 31
1777064490 31
1777064495 31
1777064500 31
1777064505 31
1777064510 31
1777064515 44
1777064520 44
1777064525 44
1777064530 44
1777064535 44
1777064540 44
1777064545 44
1777064550 44
```
</details>

---

