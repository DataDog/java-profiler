---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 07:37:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 73-82 cores)</summary>

```
1790335961 73
1790335966 73
1790335971 73
1790335976 82
1790335981 82
1790335986 82
1790335991 82
1790335996 82
1790336001 82
1790336006 82
1790336011 82
1790336016 82
1790336021 82
1790336026 82
1790336031 82
1790336036 82
1790336041 82
1790336046 82
1790336051 82
1790336056 82
```
</details>

---

