---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 03:32:30 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 571 |

<details>
<summary>CPU Timeline (4 unique values: 49-96 cores)</summary>

```
1794990479 49
1794990484 49
1794990489 49
1794990494 49
1794990499 49
1794990504 49
1794990509 49
1794990514 69
1794990519 69
1794990524 91
1794990529 91
1794990534 91
1794990539 91
1794990544 91
1794990549 91
1794990554 91
1794990559 91
1794990564 91
1794990569 91
1794990574 96
```
</details>

---

