---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:02:50 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (4 unique values: 38-51 cores)</summary>

```
1794927351 43
1794927356 43
1794927361 43
1794927366 43
1794927371 38
1794927376 38
1794927381 38
1794927386 38
1794927391 38
1794927396 38
1794927401 38
1794927406 38
1794927411 38
1794927416 38
1794927421 38
1794927426 38
1794927431 38
1794927436 38
1794927441 38
1794927446 46
```
</details>

---

