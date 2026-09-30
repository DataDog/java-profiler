---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 15:17:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 63-69 cores)</summary>

```
1790795593 69
1790795598 69
1790795603 69
1790795608 67
1790795613 67
1790795618 67
1790795623 67
1790795628 67
1790795633 67
1790795638 67
1790795643 67
1790795648 67
1790795653 67
1790795658 67
1790795663 67
1790795668 67
1790795673 67
1790795678 67
1790795683 67
1790795688 67
```
</details>

---

