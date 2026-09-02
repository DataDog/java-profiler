---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 16:51:59 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 53-69 cores)</summary>

```
1788382017 57
1788382022 57
1788382027 57
1788382032 57
1788382037 53
1788382042 53
1788382047 53
1788382052 53
1788382057 53
1788382062 53
1788382067 53
1788382072 53
1788382077 53
1788382082 53
1788382087 53
1788382092 53
1788382097 65
1788382102 65
1788382107 67
1788382112 67
```
</details>

---

