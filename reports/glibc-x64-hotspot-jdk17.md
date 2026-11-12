---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:35:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1794490188 30
1794490193 30
1794490198 30
1794490203 30
1794490208 30
1794490213 30
1794490218 30
1794490223 30
1794490228 30
1794490233 30
1794490238 30
1794490243 30
1794490248 30
1794490253 30
1794490258 30
1794490263 30
1794490268 30
1794490273 28
1794490278 28
1794490283 28
```
</details>

---

