---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-19 05:56:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 26-47 cores)</summary>

```
1792403440 33
1792403445 35
1792403450 35
1792403455 35
1792403460 35
1792403465 35
1792403470 35
1792403475 35
1792403480 32
1792403485 32
1792403490 26
1792403495 26
1792403500 26
1792403505 26
1792403510 26
1792403515 26
1792403520 26
1792403525 26
1792403530 26
1792403535 26
```
</details>

---

