---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:02:48 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 9 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1789682083 32
1789682088 32
1789682093 32
1789682098 30
1789682103 30
1789682108 30
1789682113 30
1789682118 30
1789682123 30
1789682128 30
1789682133 30
1789682138 30
1789682143 30
1789682148 30
1789682153 30
1789682158 30
1789682163 30
1789682168 30
1789682173 30
1789682178 32
```
</details>

---

