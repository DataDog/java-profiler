---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 05:16:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 12 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 50-57 cores)</summary>

```
1790327425 53
1790327430 50
1790327435 50
1790327440 50
1790327445 50
1790327450 52
1790327455 52
1790327460 52
1790327465 52
1790327470 52
1790327475 57
1790327480 57
1790327485 57
1790327490 57
1790327495 57
1790327500 57
1790327505 57
1790327510 57
1790327515 57
1790327520 57
```
</details>

---

