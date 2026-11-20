---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 06:42:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 30-50 cores)</summary>

```
1795174669 30
1795174674 30
1795174679 50
1795174684 50
1795174689 50
1795174694 50
1795174699 36
1795174704 36
1795174709 36
1795174714 36
1795174719 36
1795174724 36
1795174729 36
1795174734 36
1795174739 36
1795174744 36
1795174749 36
1795174754 36
1795174759 36
1795174764 36
```
</details>

---

