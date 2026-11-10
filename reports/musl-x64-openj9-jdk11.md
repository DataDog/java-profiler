---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 18:14:40 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (7 unique values: 47-82 cores)</summary>

```
1794352291 49
1794352297 49
1794352302 47
1794352307 47
1794352312 47
1794352317 47
1794352322 47
1794352327 47
1794352332 47
1794352337 64
1794352342 64
1794352347 64
1794352352 64
1794352357 64
1794352362 64
1794352367 64
1794352372 63
1794352377 63
1794352382 78
1794352387 78
```
</details>

---

