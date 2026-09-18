---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:29:53 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 12-15 cores)</summary>

```
1789719915 13
1789719920 13
1789719925 13
1789719930 15
1789719935 15
1789719940 15
1789719945 15
1789719950 15
1789719955 12
1789719960 12
1789719965 12
1789719970 12
1789719975 12
1789719980 12
1789719985 12
1789719990 12
1789719995 12
1789720000 12
1789720005 12
1789720010 12
```
</details>

---

