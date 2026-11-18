---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1795010720 64
1795010725 64
1795010730 64
1795010735 64
1795010740 64
1795010745 64
1795010751 64
1795010756 64
1795010761 64
1795010766 64
1795010771 64
1795010776 64
1795010781 64
1795010786 64
1795010791 64
1795010796 64
1795010801 64
1795010806 67
1795010811 67
1795010816 67
```
</details>

---

