---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 16:48:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1789677764 84
1789677769 86
1789677774 86
1789677779 86
1789677784 86
1789677789 86
1789677794 86
1789677799 86
1789677804 86
1789677809 86
1789677814 84
1789677819 84
1789677824 84
1789677829 84
1789677834 84
1789677839 84
1789677844 84
1789677849 84
1789677854 84
1789677859 84
```
</details>

---

