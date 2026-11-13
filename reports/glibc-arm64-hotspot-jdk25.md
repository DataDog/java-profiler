---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:55:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 16 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794574237 48
1794574242 48
1794574247 48
1794574252 48
1794574257 48
1794574262 48
1794574267 48
1794574272 48
1794574277 48
1794574282 48
1794574287 48
1794574292 48
1794574297 48
1794574302 48
1794574307 48
1794574312 48
1794574317 48
1794574322 48
1794574327 48
1794574332 48
```
</details>

---

