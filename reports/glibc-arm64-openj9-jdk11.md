---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:30:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (4 unique values: 31-43 cores)</summary>

```
1789719970 31
1789719975 31
1789719980 31
1789719985 31
1789719990 43
1789719995 43
1789720000 43
1789720005 43
1789720010 43
1789720015 33
1789720020 33
1789720025 38
1789720030 38
1789720035 38
1789720040 38
1789720045 38
1789720050 38
1789720055 38
1789720060 38
1789720065 43
```
</details>

---

