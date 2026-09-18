---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:30:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 13 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789737748 48
1789737753 48
1789737758 48
1789737763 48
1789737768 48
1789737773 48
1789737778 48
1789737783 48
1789737788 48
1789737793 48
1789737798 48
1789737803 48
1789737808 48
1789737813 48
1789737818 48
1789737823 43
1789737828 43
1789737833 43
1789737838 43
1789737843 43
```
</details>

---

