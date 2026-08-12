---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:38:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 50-62 cores)</summary>

```
1786523558 54
1786523563 54
1786523568 54
1786523573 54
1786523578 54
1786523583 54
1786523588 62
1786523593 62
1786523598 50
1786523603 50
1786523608 50
1786523613 50
1786523618 50
1786523623 50
1786523628 50
1786523633 50
1786523639 50
1786523644 50
1786523649 50
1786523654 50
```
</details>

---

