---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:49:09 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 12 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1794483889 70
1794483894 70
1794483899 70
1794483904 70
1794483909 70
1794483914 70
1794483919 70
1794483924 70
1794483929 70
1794483934 70
1794483939 70
1794483944 70
1794483949 70
1794483954 70
1794483959 70
1794483964 70
1794483969 72
1794483974 72
1794483979 72
1794483984 72
```
</details>

---

