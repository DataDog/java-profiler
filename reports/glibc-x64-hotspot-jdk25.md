---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:47:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 39-63 cores)</summary>

```
1794408153 51
1794408158 51
1794408163 51
1794408168 51
1794408173 51
1794408178 51
1794408183 51
1794408188 51
1794408193 39
1794408198 39
1794408203 39
1794408208 39
1794408213 39
1794408218 39
1794408223 44
1794408228 44
1794408233 44
1794408238 44
1794408243 44
1794408248 42
```
</details>

---

