---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:36:11 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 10-66 cores)</summary>

```
1795379523 10
1795379528 10
1795379533 10
1795379538 10
1795379543 10
1795379548 10
1795379553 10
1795379558 10
1795379563 38
1795379568 38
1795379573 38
1795379578 38
1795379583 38
1795379588 38
1795379593 38
1795379598 38
1795379603 38
1795379608 38
1795379613 66
1795379618 66
```
</details>

---

