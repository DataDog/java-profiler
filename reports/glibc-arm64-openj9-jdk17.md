---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 15:31:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1786390031 25
1786390036 25
1786390041 27
1786390046 27
1786390051 27
1786390056 27
1786390061 22
1786390066 22
1786390071 22
1786390076 22
1786390081 22
1786390086 22
1786390091 22
1786390096 22
1786390101 22
1786390106 22
1786390111 22
1786390116 22
1786390121 22
1786390126 22
```
</details>

---

