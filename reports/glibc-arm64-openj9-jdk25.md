---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 09:37:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1777383157 60
1777383162 60
1777383167 60
1777383172 60
1777383177 60
1777383182 60
1777383187 60
1777383192 60
1777383197 60
1777383202 60
1777383207 60
1777383212 60
1777383217 60
1777383222 64
1777383227 64
1777383232 64
1777383237 64
1777383242 64
1777383247 64
1777383252 64
```
</details>

---

