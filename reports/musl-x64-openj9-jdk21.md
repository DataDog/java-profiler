---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-05 15:03:47 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 13 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1770321471 81
1770321476 81
1770321481 81
1770321486 81
1770321491 81
1770321496 77
1770321501 77
1770321506 77
1770321511 77
1770321516 77
1770321521 77
1770321526 77
1770321531 73
1770321536 73
1770321541 73
1770321546 73
1770321551 73
1770321556 73
1770321561 73
1770321566 73
```
</details>

---

