---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 11:10:56 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1794240157 46
1794240162 46
1794240167 46
1794240172 46
1794240177 46
1794240182 46
1794240187 46
1794240192 46
1794240197 46
1794240202 46
1794240207 46
1794240212 44
1794240217 44
1794240222 44
1794240227 44
1794240232 44
1794240237 44
1794240242 44
1794240247 44
1794240252 44
```
</details>

---

