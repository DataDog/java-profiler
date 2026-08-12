---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:38:15 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 46-69 cores)</summary>

```
1786523553 69
1786523558 69
1786523563 69
1786523568 69
1786523573 69
1786523578 69
1786523583 69
1786523588 69
1786523593 69
1786523598 50
1786523603 50
1786523608 46
1786523613 46
1786523618 46
1786523623 46
1786523628 46
1786523633 46
1786523638 46
1786523643 46
1786523648 46
```
</details>

---

