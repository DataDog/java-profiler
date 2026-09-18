---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:29:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1076 |
| Sample Rate | 17.93/sec |
| Health Score | 1121% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 38-45 cores)</summary>

```
1789719925 38
1789719930 38
1789719935 38
1789719940 38
1789719945 38
1789719950 38
1789719955 38
1789719960 38
1789719965 38
1789719970 40
1789719975 40
1789719980 40
1789719985 40
1789719990 40
1789719995 40
1789720000 38
1789720005 38
1789720010 38
1789720015 38
1789720020 38
```
</details>

---

