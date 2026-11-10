---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 16:40:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 15 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1794346497 39
1794346502 39
1794346507 39
1794346512 39
1794346517 39
1794346522 39
1794346527 39
1794346532 39
1794346537 39
1794346542 39
1794346547 39
1794346552 39
1794346557 39
1794346562 39
1794346567 39
1794346572 39
1794346577 39
1794346582 51
1794346587 51
1794346592 51
```
</details>

---

