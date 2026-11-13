---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:44:21 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 10 |
| Allocations | 123 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794584405 48
1794584410 48
1794584415 48
1794584420 48
1794584425 48
1794584430 48
1794584435 43
1794584440 43
1794584445 43
1794584450 43
1794584455 43
1794584460 43
1794584465 43
1794584470 43
1794584475 43
1794584480 43
1794584485 48
1794584490 48
1794584495 48
1794584500 48
```
</details>

---

