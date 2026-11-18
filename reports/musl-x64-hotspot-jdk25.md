---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:31:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 76-79 cores)</summary>

```
1795012023 76
1795012028 76
1795012033 76
1795012038 76
1795012043 79
1795012048 79
1795012053 79
1795012058 79
1795012063 79
1795012068 79
1795012073 79
1795012078 79
1795012083 79
1795012088 79
1795012093 79
1795012098 79
1795012103 79
1795012108 79
1795012113 79
1795012118 79
```
</details>

---

