---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 09:04:52 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 7 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (5 unique values: 61-76 cores)</summary>

```
1790600394 63
1790600399 63
1790600404 61
1790600409 61
1790600414 61
1790600419 61
1790600424 61
1790600429 61
1790600435 61
1790600440 61
1790600445 61
1790600450 72
1790600455 72
1790600460 74
1790600465 74
1790600470 76
1790600475 76
1790600480 76
1790600485 76
1790600490 76
```
</details>

---

