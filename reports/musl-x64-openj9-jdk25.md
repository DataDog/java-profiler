---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 17:08:41 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 10 |
| Allocations | 570 |

<details>
<summary>CPU Timeline (2 unique values: 71-89 cores)</summary>

```
1794348225 71
1794348230 71
1794348235 71
1794348240 71
1794348245 89
1794348250 89
1794348255 89
1794348260 89
1794348265 89
1794348270 89
1794348275 89
1794348280 89
1794348285 89
1794348290 89
1794348295 89
1794348300 89
1794348305 89
1794348311 89
1794348316 89
1794348321 89
```
</details>

---

