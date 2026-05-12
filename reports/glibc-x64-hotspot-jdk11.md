---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 05:49:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1100 |
| Sample Rate | 18.33/sec |
| Health Score | 1146% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 58-68 cores)</summary>

```
1778579079 58
1778579084 58
1778579089 58
1778579094 58
1778579099 58
1778579104 58
1778579109 58
1778579114 58
1778579119 58
1778579124 63
1778579129 63
1778579134 63
1778579139 63
1778579144 63
1778579149 68
1778579154 68
1778579159 68
1778579164 68
1778579169 68
1778579174 68
```
</details>

---

