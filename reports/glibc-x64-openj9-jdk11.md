---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 12:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1786119573 62
1786119578 62
1786119583 62
1786119588 62
1786119593 62
1786119598 62
1786119603 62
1786119608 60
1786119613 60
1786119618 58
1786119623 58
1786119628 58
1786119633 58
1786119638 58
1786119643 58
1786119648 60
1786119653 60
1786119658 60
1786119663 60
1786119668 60
```
</details>

---

