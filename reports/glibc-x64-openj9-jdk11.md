---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 07:51:09 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1795610773 87
1795610778 87
1795610783 87
1795610788 87
1795610793 87
1795610798 87
1795610803 87
1795610808 87
1795610813 87
1795610818 87
1795610823 87
1795610828 87
1795610833 87
1795610838 96
1795610843 96
1795610848 96
1795610853 96
1795610858 96
1795610863 96
1795610868 96
```
</details>

---

