---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 07:04:04 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (3 unique values: 50-57 cores)</summary>

```
1795175957 57
1795175962 57
1795175967 57
1795175972 57
1795175977 57
1795175982 57
1795175987 57
1795175992 52
1795175997 52
1795176002 52
1795176007 52
1795176012 52
1795176017 52
1795176023 52
1795176028 52
1795176033 52
1795176038 52
1795176043 52
1795176048 52
1795176053 52
```
</details>

---

