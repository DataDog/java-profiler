---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 14:50:19 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 49-81 cores)</summary>

```
1795031126 51
1795031131 51
1795031136 51
1795031141 51
1795031146 51
1795031151 49
1795031156 49
1795031161 49
1795031166 49
1795031171 49
1795031176 49
1795031181 49
1795031186 49
1795031191 51
1795031196 51
1795031201 51
1795031206 51
1795031211 81
1795031216 81
1795031221 81
```
</details>

---

