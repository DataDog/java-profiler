---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 13:48:59 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1793382289 61
1793382294 61
1793382299 61
1793382304 61
1793382309 61
1793382314 61
1793382319 61
1793382324 61
1793382329 61
1793382334 61
1793382339 61
1793382344 61
1793382349 61
1793382354 61
1793382359 61
1793382364 61
1793382369 61
1793382374 61
1793382379 61
1793382384 63
```
</details>

---

