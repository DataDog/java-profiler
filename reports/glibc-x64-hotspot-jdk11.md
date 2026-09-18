---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:33:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 8-32 cores)</summary>

```
1789719925 32
1789719930 32
1789719935 32
1789719940 32
1789719945 32
1789719950 32
1789719955 8
1789719960 8
1789719965 8
1789719970 8
1789719975 8
1789719980 8
1789719985 8
1789719990 8
1789719995 8
1789720000 8
1789720005 8
1789720010 8
1789720015 8
1789720020 8
```
</details>

---

