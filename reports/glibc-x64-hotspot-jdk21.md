---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-22 13:04:04 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 42-49 cores)</summary>

```
1776876841 49
1776876846 49
1776876851 45
1776876856 45
1776876861 45
1776876866 45
1776876871 45
1776876876 45
1776876881 49
1776876886 49
1776876891 45
1776876896 45
1776876901 42
1776876906 42
1776876911 42
1776876916 42
1776876921 42
1776876926 42
1776876931 42
1776876936 42
```
</details>

---

