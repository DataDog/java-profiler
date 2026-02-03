---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:55:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1770137445 26
1770137450 26
1770137455 26
1770137460 26
1770137465 30
1770137470 30
1770137475 30
1770137480 30
1770137485 30
1770137490 30
1770137495 30
1770137500 30
1770137505 29
1770137510 29
1770137515 29
1770137520 29
1770137525 29
1770137530 29
1770137535 29
1770137540 32
```
</details>

---

