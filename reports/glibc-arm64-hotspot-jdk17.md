---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:21:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777857366 59
1777857371 59
1777857376 59
1777857381 59
1777857386 59
1777857391 59
1777857396 59
1777857401 59
1777857406 59
1777857411 59
1777857416 59
1777857421 64
1777857426 64
1777857431 64
1777857436 64
1777857441 64
1777857446 64
1777857451 64
1777857456 64
1777857461 64
```
</details>

---

