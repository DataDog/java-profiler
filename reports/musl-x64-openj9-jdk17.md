---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 07:01:54 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 18.07/sec |
| Health Score | 1129% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 25.70/sec |
| Health Score | 1606% |
| Threads | 10 |
| Allocations | 462 |

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
1769687595 70
1769687600 66
1769687605 66
1769687610 63
1769687615 63
```
</details>

---

