---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 05:49:18 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 13 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 25-59 cores)</summary>

```
1786441490 25
1786441495 25
1786441500 25
1786441505 25
1786441510 25
1786441515 25
1786441520 25
1786441525 25
1786441530 25
1786441535 25
1786441540 25
1786441545 25
1786441550 25
1786441555 25
1786441560 59
1786441565 59
1786441570 59
1786441575 59
1786441580 59
1786441585 59
```
</details>

---

