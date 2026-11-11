---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:47:13 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1794408207 40
1794408212 40
1794408217 44
1794408222 44
1794408227 44
1794408232 44
1794408237 44
1794408242 44
1794408247 44
1794408252 44
1794408257 48
1794408262 48
1794408267 48
1794408272 48
1794408277 48
1794408282 48
1794408287 48
1794408292 48
1794408297 48
1794408302 48
```
</details>

---

