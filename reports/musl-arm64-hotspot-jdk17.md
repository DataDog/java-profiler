---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 08:39:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1787661345 44
1787661350 44
1787661355 44
1787661360 46
1787661365 46
1787661370 46
1787661375 46
1787661380 46
1787661385 46
1787661391 46
1787661396 46
1787661401 46
1787661406 46
1787661411 46
1787661416 46
1787661421 46
1787661426 46
1787661431 46
1787661436 46
1787661441 46
```
</details>

---

