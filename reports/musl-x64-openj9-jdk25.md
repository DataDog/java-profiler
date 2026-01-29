---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 07:01:54 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 25.23/sec |
| Health Score | 1577% |
| Threads | 11 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 919 |
| Sample Rate | 30.63/sec |
| Health Score | 1914% |
| Threads | 12 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 63-89 cores)</summary>

```
1769687520 70
1769687525 70
1769687530 70
1769687535 70
1769687540 70
1769687545 70
1769687550 70
1769687555 70
1769687560 70
1769687565 70
1769687570 70
1769687575 70
1769687580 70
1769687585 70
1769687590 70
1769687595 66
1769687600 66
1769687605 66
1769687610 63
1769687615 63
```
</details>

---

