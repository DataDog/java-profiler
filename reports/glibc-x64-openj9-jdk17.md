---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:01:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1795607794 93
1795607799 93
1795607804 93
1795607809 93
1795607814 93
1795607819 93
1795607824 93
1795607829 93
1795607834 93
1795607839 96
1795607844 96
1795607849 96
1795607854 96
1795607859 96
1795607864 96
1795607869 96
1795607874 96
1795607879 96
1795607884 96
1795607889 96
```
</details>

---

