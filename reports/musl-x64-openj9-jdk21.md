---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:20:53 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1795641345 40
1795641350 40
1795641355 40
1795641360 40
1795641365 40
1795641370 40
1795641375 40
1795641380 40
1795641385 40
1795641390 40
1795641395 40
1795641400 40
1795641405 40
1795641410 40
1795641415 40
1795641420 40
1795641425 42
1795641430 42
1795641435 42
1795641440 42
```
</details>

---

