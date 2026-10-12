---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 03:21:24 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 9 |
| Allocations | 127 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1791789392 34
1791789397 34
1791789402 34
1791789407 34
1791789412 34
1791789417 34
1791789422 34
1791789427 22
1791789432 22
1791789437 22
1791789442 22
1791789447 22
1791789452 22
1791789457 22
1791789462 22
1791789467 22
1791789472 22
1791789477 22
1791789482 22
1791789487 17
```
</details>

---

