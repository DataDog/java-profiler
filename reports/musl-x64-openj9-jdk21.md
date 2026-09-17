---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:41:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 35-59 cores)</summary>

```
1789673570 59
1789673575 59
1789673580 59
1789673585 59
1789673590 43
1789673595 43
1789673600 35
1789673605 35
1789673610 35
1789673615 35
1789673620 35
1789673625 35
1789673630 35
1789673635 35
1789673640 35
1789673645 35
1789673650 35
1789673655 35
1789673660 35
1789673665 35
```
</details>

---

