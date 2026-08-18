---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 13:40:53 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 10 |
| Allocations | 322 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 11 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 72-88 cores)</summary>

```
1787074547 72
1787074552 72
1787074557 72
1787074562 72
1787074567 72
1787074572 72
1787074577 72
1787074582 72
1787074587 72
1787074592 72
1787074597 72
1787074602 88
1787074607 88
1787074612 88
1787074617 88
1787074622 88
1787074627 88
1787074632 88
1787074637 88
1787074642 88
```
</details>

---

