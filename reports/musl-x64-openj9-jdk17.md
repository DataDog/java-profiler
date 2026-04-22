---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 12:39:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 79-84 cores)</summary>

```
1776875618 79
1776875623 79
1776875628 79
1776875633 79
1776875638 79
1776875643 79
1776875648 84
1776875653 84
1776875658 84
1776875663 84
1776875668 84
1776875673 84
1776875678 84
1776875683 84
1776875688 84
1776875693 84
1776875699 84
1776875704 84
1776875709 80
1776875714 80
```
</details>

---

