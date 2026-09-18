---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:28:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 12-15 cores)</summary>

```
1789719920 13
1789719925 13
1789719930 13
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
1789720015 12
```
</details>

---

