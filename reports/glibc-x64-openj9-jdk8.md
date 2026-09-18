---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 04:28:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 54-74 cores)</summary>

```
1789719940 54
1789719945 54
1789719950 74
1789719955 74
1789719960 74
1789719965 74
1789719970 74
1789719975 74
1789719980 74
1789719985 74
1789719990 74
1789719995 74
1789720000 74
1789720005 74
1789720010 74
1789720015 74
1789720020 74
1789720025 74
1789720030 74
1789720035 74
```
</details>

---

