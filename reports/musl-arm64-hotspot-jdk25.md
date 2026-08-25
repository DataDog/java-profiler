---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 08:39:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 30-44 cores)</summary>

```
1787661341 30
1787661346 30
1787661351 30
1787661356 30
1787661361 30
1787661366 30
1787661371 42
1787661376 42
1787661381 42
1787661386 42
1787661391 42
1787661396 42
1787661401 42
1787661406 44
1787661411 44
1787661416 44
1787661421 44
1787661426 44
1787661431 44
1787661436 44
```
</details>

---

