---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 19:07:45 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 57-63 cores)</summary>

```
1793836926 63
1793836931 63
1793836936 63
1793836941 63
1793836946 63
1793836951 63
1793836956 63
1793836961 63
1793836966 63
1793836971 63
1793836976 63
1793836981 57
1793836986 57
1793836991 60
1793836996 60
1793837001 58
1793837006 58
1793837011 58
1793837016 58
1793837021 58
```
</details>

---

