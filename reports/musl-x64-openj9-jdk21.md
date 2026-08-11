---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 14:11:50 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 52-68 cores)</summary>

```
1786471573 52
1786471578 52
1786471583 52
1786471588 52
1786471593 52
1786471598 52
1786471603 52
1786471608 52
1786471613 52
1786471618 52
1786471623 52
1786471628 52
1786471633 52
1786471638 52
1786471643 52
1786471648 52
1786471653 52
1786471658 52
1786471663 52
1786471668 60
```
</details>

---

