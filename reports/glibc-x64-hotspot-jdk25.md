---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:02:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1794927458 84
1794927463 84
1794927468 84
1794927473 84
1794927478 84
1794927483 84
1794927489 84
1794927494 84
1794927499 84
1794927504 86
1794927509 86
1794927514 84
1794927519 84
1794927524 84
1794927529 84
1794927534 84
1794927539 84
1794927544 84
1794927549 84
1794927554 84
```
</details>

---

