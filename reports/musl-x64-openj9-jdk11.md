---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:40:57 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 575 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794573200 59
1794573205 59
1794573210 59
1794573215 59
1794573220 59
1794573225 59
1794573230 59
1794573235 59
1794573240 59
1794573245 59
1794573250 59
1794573255 59
1794573260 59
1794573265 59
1794573270 59
1794573275 59
1794573280 61
1794573285 61
1794573290 61
1794573295 61
```
</details>

---

