---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 09:12:49 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (7 unique values: 36-44 cores)</summary>

```
1794319683 43
1794319688 41
1794319693 41
1794319698 41
1794319703 41
1794319708 41
1794319713 41
1794319718 41
1794319723 41
1794319728 39
1794319733 39
1794319738 39
1794319743 39
1794319748 39
1794319753 44
1794319758 44
1794319763 36
1794319768 36
1794319773 36
1794319778 38
```
</details>

---

