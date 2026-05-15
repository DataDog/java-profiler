---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-15 08:44:40 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 26-38 cores)</summary>

```
1778848643 38
1778848648 38
1778848653 38
1778848658 38
1778848663 38
1778848668 38
1778848673 38
1778848678 38
1778848683 38
1778848688 35
1778848693 35
1778848698 26
1778848703 26
1778848708 26
1778848713 26
1778848718 26
1778848723 26
1778848728 26
1778848733 26
1778848738 31
```
</details>

---

