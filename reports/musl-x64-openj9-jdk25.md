---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:44:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 83-88 cores)</summary>

```
1794584400 83
1794584405 83
1794584410 83
1794584415 83
1794584420 83
1794584425 83
1794584430 83
1794584435 83
1794584440 83
1794584445 83
1794584450 83
1794584455 83
1794584460 83
1794584465 86
1794584470 86
1794584475 86
1794584480 88
1794584485 88
1794584490 88
1794584495 88
```
</details>

---

