---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 00:53:03 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 13 |
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
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 13-18 cores)</summary>

```
1792385361 16
1792385366 18
1792385371 18
1792385376 18
1792385381 18
1792385386 18
1792385391 18
1792385396 18
1792385401 18
1792385406 18
1792385411 18
1792385416 18
1792385421 18
1792385426 18
1792385431 18
1792385436 18
1792385441 18
1792385446 18
1792385451 18
1792385456 18
```
</details>

---

