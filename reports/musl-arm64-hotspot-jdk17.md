---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 09:32:24 EDT

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
| CPU Cores (start) | 37 |
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
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1786368402 37
1786368407 37
1786368412 37
1786368417 37
1786368422 37
1786368427 37
1786368432 37
1786368437 37
1786368442 37
1786368447 37
1786368452 37
1786368457 37
1786368462 43
1786368467 43
1786368472 43
1786368477 43
1786368482 43
1786368487 43
1786368492 43
1786368497 43
```
</details>

---

