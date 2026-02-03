---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 03:50:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (6 unique values: 51-82 cores)</summary>

```
1770108220 51
1770108225 51
1770108230 72
1770108235 72
1770108240 72
1770108245 72
1770108250 76
1770108255 76
1770108260 76
1770108265 76
1770108270 76
1770108275 76
1770108280 67
1770108285 67
1770108290 67
1770108295 67
1770108300 67
1770108305 67
1770108310 67
1770108315 67
```
</details>

---

