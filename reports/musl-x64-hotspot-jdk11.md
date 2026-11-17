---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:55:34 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 71-75 cores)</summary>

```
1794945027 75
1794945032 75
1794945037 75
1794945042 75
1794945047 75
1794945052 75
1794945057 75
1794945062 75
1794945067 75
1794945072 75
1794945077 75
1794945082 75
1794945087 75
1794945092 75
1794945097 71
1794945102 71
1794945107 74
1794945112 74
1794945117 74
1794945122 74
```
</details>

---

