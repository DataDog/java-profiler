---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 08:57:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1776257544 28
1776257549 28
1776257554 28
1776257559 28
1776257564 28
1776257569 28
1776257574 28
1776257579 33
1776257584 33
1776257589 33
1776257594 33
1776257599 33
1776257604 33
1776257609 33
1776257614 33
1776257619 33
1776257624 33
1776257629 33
1776257634 33
1776257639 33
```
</details>

---

