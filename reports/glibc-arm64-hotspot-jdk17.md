---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 06:28:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 36-38 cores)</summary>

```
1795087384 38
1795087389 38
1795087394 38
1795087399 36
1795087404 36
1795087409 36
1795087414 36
1795087419 36
1795087424 36
1795087429 36
1795087434 36
1795087439 36
1795087444 36
1795087449 37
1795087454 37
1795087459 38
1795087464 38
1795087469 38
1795087474 38
1795087479 38
```
</details>

---

