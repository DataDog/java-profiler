---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 07:19:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1795004101 48
1795004106 48
1795004111 48
1795004116 48
1795004121 48
1795004126 48
1795004131 46
1795004136 46
1795004141 46
1795004146 44
1795004151 44
1795004156 44
1795004161 44
1795004166 48
1795004171 48
1795004176 48
1795004181 48
1795004186 48
1795004191 48
1795004196 46
```
</details>

---

