---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:28:43 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (5 unique values: 79-89 cores)</summary>

```
1794392571 82
1794392576 82
1794392581 84
1794392586 84
1794392591 84
1794392596 84
1794392601 84
1794392606 84
1794392611 86
1794392616 86
1794392621 86
1794392626 86
1794392632 79
1794392637 79
1794392642 79
1794392647 79
1794392652 79
1794392657 79
1794392662 79
1794392667 79
```
</details>

---

