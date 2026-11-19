---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:12:34 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (4 unique values: 74-92 cores)</summary>

```
1795097271 86
1795097276 86
1795097281 86
1795097286 92
1795097291 92
1795097296 92
1795097301 92
1795097306 92
1795097311 92
1795097316 92
1795097321 92
1795097326 92
1795097331 92
1795097336 92
1795097341 92
1795097346 92
1795097351 92
1795097356 92
1795097361 74
1795097366 74
```
</details>

---

