---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:05:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 76-91 cores)</summary>

```
1795449522 76
1795449527 76
1795449532 76
1795449537 76
1795449542 76
1795449547 76
1795449552 76
1795449557 76
1795449562 80
1795449567 80
1795449572 80
1795449577 80
1795449582 80
1795449587 80
1795449592 80
1795449597 80
1795449602 80
1795449607 80
1795449612 80
1795449617 82
```
</details>

---

