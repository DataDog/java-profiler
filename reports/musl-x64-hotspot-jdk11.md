---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 01:05:34 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791522006 30
1791522011 30
1791522016 30
1791522021 30
1791522026 30
1791522031 30
1791522036 30
1791522041 30
1791522046 30
1791522051 30
1791522056 30
1791522061 32
1791522066 32
1791522071 32
1791522076 32
1791522081 32
1791522086 32
1791522091 32
1791522096 32
1791522101 32
```
</details>

---

