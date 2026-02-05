---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-05 05:01:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 12 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1770285113 54
1770285118 54
1770285123 54
1770285128 54
1770285133 54
1770285138 54
1770285143 54
1770285148 54
1770285153 54
1770285158 54
1770285163 54
1770285168 54
1770285173 54
1770285178 54
1770285183 54
1770285188 54
1770285193 54
1770285198 54
1770285203 54
1770285208 64
```
</details>

---

