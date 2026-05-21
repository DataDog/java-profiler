---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-21 08:14:53 EDT

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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1779365391 64
1779365396 64
1779365401 64
1779365406 64
1779365411 64
1779365416 64
1779365421 64
1779365426 64
1779365431 64
1779365436 64
1779365441 64
1779365446 64
1779365451 64
1779365456 64
1779365461 64
1779365466 64
1779365471 64
1779365476 64
1779365481 64
1779365486 64
```
</details>

---

