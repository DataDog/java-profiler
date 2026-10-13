---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-13 01:03:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 41-61 cores)</summary>

```
1791867580 61
1791867585 61
1791867590 61
1791867596 61
1791867601 61
1791867606 61
1791867611 61
1791867616 61
1791867621 61
1791867626 61
1791867631 61
1791867636 41
1791867641 41
1791867646 41
1791867651 41
1791867656 41
1791867661 41
1791867666 41
1791867671 41
1791867676 41
```
</details>

---

