---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-60 cores)</summary>

```
1790678279 44
1790678284 44
1790678289 44
1790678294 44
1790678299 44
1790678304 44
1790678309 44
1790678314 44
1790678319 44
1790678324 44
1790678329 40
1790678334 40
1790678339 40
1790678344 40
1790678349 40
1790678354 40
1790678359 40
1790678364 40
1790678369 40
1790678374 40
```
</details>

---

