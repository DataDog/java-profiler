---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 19:10:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (5 unique values: 38-48 cores)</summary>

```
1789686360 38
1789686365 43
1789686370 43
1789686375 41
1789686380 41
1789686385 41
1789686390 41
1789686395 41
1789686400 41
1789686405 41
1789686410 41
1789686415 41
1789686420 41
1789686425 41
1789686430 41
1789686435 41
1789686440 41
1789686445 41
1789686450 46
1789686455 46
```
</details>

---

