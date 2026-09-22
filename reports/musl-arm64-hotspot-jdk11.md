---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 00:56:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 18-26 cores)</summary>

```
1790052754 26
1790052759 26
1790052764 26
1790052769 26
1790052774 26
1790052779 26
1790052784 21
1790052789 21
1790052794 18
1790052799 18
1790052804 18
1790052809 18
1790052814 18
1790052819 18
1790052824 18
1790052829 18
1790052834 23
1790052839 23
1790052844 23
1790052849 23
```
</details>

---

