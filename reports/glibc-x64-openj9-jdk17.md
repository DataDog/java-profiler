---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:12:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1795097241 75
1795097246 75
1795097251 75
1795097256 75
1795097261 75
1795097266 75
1795097271 75
1795097276 78
1795097281 78
1795097286 78
1795097291 78
1795097296 78
1795097301 78
1795097306 78
1795097311 76
1795097316 76
1795097321 76
1795097326 76
1795097331 76
1795097336 76
```
</details>

---

