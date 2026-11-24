---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:15:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 8 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 41-50 cores)</summary>

```
1795514955 44
1795514960 44
1795514965 50
1795514970 50
1795514975 50
1795514980 50
1795514985 50
1795514990 50
1795514995 50
1795515000 50
1795515005 41
1795515010 41
1795515015 41
1795515020 41
1795515025 41
1795515030 41
1795515035 41
1795515040 41
1795515045 41
1795515050 41
```
</details>

---

