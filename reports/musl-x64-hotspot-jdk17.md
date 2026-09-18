---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:29:07 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 43-57 cores)</summary>

```
1789737729 43
1789737734 43
1789737739 43
1789737744 43
1789737749 43
1789737754 43
1789737759 43
1789737764 43
1789737769 43
1789737774 57
1789737779 57
1789737784 57
1789737789 57
1789737794 57
1789737799 57
1789737804 57
1789737809 57
1789737814 57
1789737819 57
1789737824 57
```
</details>

---

