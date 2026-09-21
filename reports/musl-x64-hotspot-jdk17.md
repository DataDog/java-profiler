---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 07:59:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1018 |
| Sample Rate | 16.97/sec |
| Health Score | 1061% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 59-84 cores)</summary>

```
1789991744 61
1789991749 61
1789991754 61
1789991759 61
1789991764 61
1789991769 61
1789991774 61
1789991779 61
1789991784 61
1789991789 61
1789991794 61
1789991799 61
1789991804 61
1789991809 61
1789991814 61
1789991819 61
1789991824 59
1789991829 59
1789991834 59
1789991839 84
```
</details>

---

