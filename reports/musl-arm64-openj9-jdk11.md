---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:29:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795098367 50
1795098372 50
1795098377 50
1795098382 50
1795098387 50
1795098392 50
1795098397 50
1795098402 50
1795098407 50
1795098412 50
1795098417 50
1795098422 50
1795098427 50
1795098432 50
1795098437 50
1795098442 50
1795098447 50
1795098452 50
1795098457 50
1795098462 50
```
</details>

---

