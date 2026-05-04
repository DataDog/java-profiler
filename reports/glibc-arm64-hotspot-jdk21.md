---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-03 21:21:04 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857347 64
1777857352 64
1777857357 64
1777857362 64
1777857367 64
1777857372 64
1777857377 64
1777857382 64
1777857387 64
1777857393 64
1777857398 64
1777857403 64
1777857408 64
1777857413 64
1777857418 64
1777857423 64
1777857428 64
1777857433 64
1777857438 64
1777857443 64
```
</details>

---

