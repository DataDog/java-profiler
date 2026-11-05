---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 19:07:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 11 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793836941 48
1793836946 48
1793836951 48
1793836956 48
1793836961 48
1793836966 48
1793836971 48
1793836976 48
1793836981 48
1793836986 48
1793836991 48
1793836996 48
1793837001 48
1793837006 48
1793837011 48
1793837016 48
1793837021 48
1793837026 48
1793837031 48
1793837036 48
```
</details>

---

