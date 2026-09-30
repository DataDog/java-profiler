---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 15:17:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 870 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 56-63 cores)</summary>

```
1790795568 56
1790795573 56
1790795578 56
1790795583 56
1790795588 63
1790795593 63
1790795598 63
1790795603 63
1790795608 63
1790795613 63
1790795618 63
1790795623 63
1790795628 63
1790795633 63
1790795638 63
1790795643 63
1790795648 63
1790795653 63
1790795659 63
1790795664 63
```
</details>

---

