---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 00:56:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 27-60 cores)</summary>

```
1790052754 50
1790052759 50
1790052764 50
1790052769 50
1790052774 50
1790052779 50
1790052784 50
1790052789 50
1790052794 50
1790052799 50
1790052804 50
1790052809 50
1790052814 60
1790052819 60
1790052824 60
1790052829 60
1790052834 60
1790052839 60
1790052844 27
1790052849 27
```
</details>

---

