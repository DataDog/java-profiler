---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:45:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 568 |

<details>
<summary>CPU Timeline (4 unique values: 65-68 cores)</summary>

```
1794497514 66
1794497519 66
1794497524 66
1794497529 66
1794497534 66
1794497539 66
1794497544 66
1794497549 68
1794497554 68
1794497559 68
1794497564 68
1794497569 65
1794497574 65
1794497579 65
1794497584 65
1794497589 65
1794497594 65
1794497599 67
1794497604 67
1794497609 67
```
</details>

---

