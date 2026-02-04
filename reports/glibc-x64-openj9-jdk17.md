---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-04 14:09:43 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 54-60 cores)</summary>

```
1770231841 60
1770231846 60
1770231851 60
1770231856 60
1770231861 54
1770231866 54
1770231871 54
1770231876 54
1770231881 54
1770231886 54
1770231891 54
1770231896 54
1770231901 54
1770231906 54
1770231911 54
1770231916 54
1770231921 54
1770231926 58
1770231931 58
1770231936 58
```
</details>

---

