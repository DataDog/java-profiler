---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 14:43:11 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 15-24 cores)</summary>

```
1777487728 24
1777487733 24
1777487738 24
1777487743 24
1777487748 24
1777487753 24
1777487758 24
1777487763 19
1777487768 19
1777487773 19
1777487778 19
1777487783 15
1777487788 15
1777487793 15
1777487798 15
1777487803 15
1777487808 15
1777487813 15
1777487818 15
1777487823 15
```
</details>

---

