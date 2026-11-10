---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:31:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 15 |
| Allocations | 181 |

<details>
<summary>CPU Timeline (5 unique values: 46-58 cores)</summary>

```
1794324432 56
1794324437 56
1794324442 55
1794324447 55
1794324452 55
1794324457 55
1794324462 55
1794324467 55
1794324472 55
1794324477 58
1794324482 58
1794324487 58
1794324492 58
1794324497 58
1794324502 58
1794324507 58
1794324512 58
1794324517 58
1794324523 58
1794324528 58
```
</details>

---

