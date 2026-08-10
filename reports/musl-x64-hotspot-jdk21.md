---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 06:26:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (4 unique values: 42-74 cores)</summary>

```
1786357274 42
1786357279 42
1786357284 42
1786357289 42
1786357294 42
1786357299 42
1786357304 42
1786357309 42
1786357314 74
1786357319 74
1786357324 74
1786357329 74
1786357334 66
1786357339 66
1786357344 66
1786357349 66
1786357354 57
1786357359 57
1786357364 57
1786357369 57
```
</details>

---

