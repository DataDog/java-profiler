---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:29:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 8 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 28-61 cores)</summary>

```
1789719895 28
1789719900 28
1789719905 28
1789719910 28
1789719915 28
1789719920 28
1789719925 28
1789719930 28
1789719935 28
1789719940 61
1789719945 61
1789719950 30
1789719955 30
1789719960 30
1789719965 30
1789719970 30
1789719975 30
1789719980 28
1789719985 28
1789719990 28
```
</details>

---

