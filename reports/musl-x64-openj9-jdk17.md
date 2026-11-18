---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:30:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (6 unique values: 20-48 cores)</summary>

```
1794997490 29
1794997495 29
1794997500 29
1794997505 29
1794997510 29
1794997515 29
1794997520 29
1794997525 29
1794997530 29
1794997535 29
1794997540 26
1794997545 26
1794997550 24
1794997555 24
1794997560 24
1794997565 24
1794997570 31
1794997575 31
1794997580 31
1794997585 31
```
</details>

---

