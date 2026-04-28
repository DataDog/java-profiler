---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 09:37:40 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (5 unique values: 47-58 cores)</summary>

```
1777383157 47
1777383162 47
1777383167 47
1777383172 55
1777383177 55
1777383182 55
1777383187 56
1777383192 56
1777383197 58
1777383202 58
1777383207 58
1777383212 57
1777383217 57
1777383222 57
1777383227 57
1777383232 57
1777383237 57
1777383242 57
1777383247 57
1777383252 57
```
</details>

---

