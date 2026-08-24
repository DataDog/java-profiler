---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-23 21:24:26 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787534410 64
1787534415 64
1787534420 64
1787534425 64
1787534430 64
1787534435 64
1787534440 64
1787534445 64
1787534450 64
1787534455 64
1787534460 64
1787534465 64
1787534470 64
1787534475 64
1787534480 64
1787534485 64
1787534490 64
1787534495 64
1787534500 64
1787534505 64
```
</details>

---

