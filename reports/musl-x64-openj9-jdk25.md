---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 14:32:14 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1776968715 28
1776968720 28
1776968725 28
1776968730 28
1776968735 28
1776968740 28
1776968745 28
1776968750 28
1776968755 28
1776968760 28
1776968765 28
1776968770 28
1776968775 28
1776968780 28
1776968785 28
1776968790 28
1776968795 28
1776968800 30
1776968805 30
1776968810 30
```
</details>

---

