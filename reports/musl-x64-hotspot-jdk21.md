---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 00:56:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 26-58 cores)</summary>

```
1790052748 55
1790052753 55
1790052759 55
1790052764 55
1790052769 55
1790052774 55
1790052779 57
1790052784 57
1790052789 57
1790052794 57
1790052799 57
1790052804 58
1790052809 58
1790052814 58
1790052819 58
1790052824 26
1790052829 26
1790052834 26
1790052839 26
1790052844 26
```
</details>

---

