---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 05:47:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1795344201 51
1795344206 51
1795344211 51
1795344216 51
1795344221 51
1795344226 51
1795344231 51
1795344236 51
1795344241 51
1795344246 51
1795344251 51
1795344256 47
1795344261 47
1795344266 47
1795344271 47
1795344276 49
1795344281 49
1795344286 49
1795344291 49
1795344296 49
```
</details>

---

