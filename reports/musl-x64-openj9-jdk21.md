---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 04:32:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 63-68 cores)</summary>

```
1791966410 68
1791966415 68
1791966420 68
1791966425 68
1791966430 68
1791966435 68
1791966440 68
1791966445 68
1791966450 68
1791966455 68
1791966460 63
1791966465 63
1791966470 63
1791966475 63
1791966480 63
1791966485 63
1791966490 63
1791966495 63
1791966500 63
1791966505 63
```
</details>

---

