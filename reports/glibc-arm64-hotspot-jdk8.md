---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-06 09:30:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 33-43 cores)</summary>

```
1791293068 41
1791293073 41
1791293078 41
1791293083 41
1791293088 41
1791293093 41
1791293098 41
1791293103 41
1791293108 41
1791293113 43
1791293118 43
1791293123 43
1791293128 43
1791293133 43
1791293138 43
1791293143 43
1791293148 43
1791293153 39
1791293158 39
1791293163 39
```
</details>

---

