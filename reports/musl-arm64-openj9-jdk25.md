---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 36-48 cores)</summary>

```
1793830729 36
1793830734 36
1793830739 36
1793830744 36
1793830749 36
1793830754 36
1793830759 43
1793830764 43
1793830769 43
1793830774 43
1793830779 43
1793830784 48
1793830789 48
1793830794 48
1793830799 48
1793830804 48
1793830809 48
1793830814 48
1793830820 48
1793830825 46
```
</details>

---

