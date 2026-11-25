---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:18:56 EST

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
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 35-87 cores)</summary>

```
1795626798 87
1795626803 87
1795626808 87
1795626813 87
1795626818 87
1795626823 87
1795626828 57
1795626833 57
1795626838 35
1795626843 35
1795626848 35
1795626853 35
1795626858 35
1795626863 35
1795626868 35
1795626873 35
1795626878 35
1795626883 35
1795626888 35
1795626893 35
```
</details>

---

