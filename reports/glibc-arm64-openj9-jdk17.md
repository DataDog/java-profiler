---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-16 07:29:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 12 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 15 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789557921 43
1789557926 43
1789557932 43
1789557937 48
1789557942 48
1789557947 48
1789557952 48
1789557957 48
1789557962 48
1789557967 48
1789557972 48
1789557977 48
1789557982 48
1789557987 48
1789557992 48
1789557997 48
1789558002 48
1789558007 48
1789558012 48
1789558017 48
```
</details>

---

