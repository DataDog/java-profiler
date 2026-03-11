---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 13:39:51 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 24-32 cores)</summary>

```
1773250230 27
1773250235 27
1773250240 28
1773250245 28
1773250250 24
1773250255 24
1773250260 24
1773250265 24
1773250270 24
1773250275 24
1773250280 24
1773250285 24
1773250290 24
1773250295 24
1773250300 24
1773250305 24
1773250310 24
1773250315 24
1773250320 24
1773250325 24
```
</details>

---

