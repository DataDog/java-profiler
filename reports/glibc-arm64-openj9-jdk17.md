---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 16:05:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 9 |
| Allocations | 197 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793739714 46
1793739719 46
1793739724 46
1793739729 46
1793739734 46
1793739739 51
1793739744 51
1793739749 51
1793739754 51
1793739759 51
1793739764 51
1793739769 51
1793739774 51
1793739779 51
1793739784 51
1793739789 51
1793739794 51
1793739799 51
1793739804 51
1793739809 51
```
</details>

---

