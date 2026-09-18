---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:29:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 39-57 cores)</summary>

```
1789737704 39
1789737709 39
1789737714 39
1789737719 39
1789737724 39
1789737729 39
1789737734 39
1789737739 39
1789737744 39
1789737749 57
1789737754 57
1789737759 57
1789737764 57
1789737769 57
1789737774 57
1789737779 57
1789737784 57
1789737789 57
1789737794 57
1789737799 57
```
</details>

---

