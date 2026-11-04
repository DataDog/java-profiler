---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1793830739 48
1793830744 48
1793830749 48
1793830754 48
1793830759 48
1793830764 48
1793830769 48
1793830774 48
1793830779 53
1793830784 53
1793830789 53
1793830794 53
1793830799 53
1793830804 53
1793830809 53
1793830814 53
1793830819 53
1793830824 53
1793830829 53
1793830834 53
```
</details>

---

