---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:31:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 58-75 cores)</summary>

```
1795012018 75
1795012023 75
1795012028 75
1795012033 75
1795012038 75
1795012043 75
1795012048 75
1795012053 75
1795012058 75
1795012063 75
1795012068 75
1795012073 58
1795012078 58
1795012083 58
1795012088 58
1795012093 58
1795012098 58
1795012103 58
1795012108 58
1795012113 58
```
</details>

---

