---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:23:46 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 74-83 cores)</summary>

```
1795627081 74
1795627086 74
1795627091 74
1795627096 74
1795627101 83
1795627106 83
1795627111 83
1795627116 83
1795627121 83
1795627126 81
1795627131 81
1795627136 81
1795627141 81
1795627146 81
1795627151 81
1795627156 81
1795627161 81
1795627166 81
1795627171 81
1795627176 81
```
</details>

---

