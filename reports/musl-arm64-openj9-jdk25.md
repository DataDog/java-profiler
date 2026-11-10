---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 15:03:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 14 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794340545 46
1794340550 46
1794340555 46
1794340560 46
1794340565 46
1794340570 46
1794340575 46
1794340580 46
1794340585 46
1794340590 46
1794340595 46
1794340600 46
1794340605 46
1794340610 46
1794340615 46
1794340620 51
1794340625 51
1794340630 51
1794340635 51
1794340640 51
```
</details>

---

