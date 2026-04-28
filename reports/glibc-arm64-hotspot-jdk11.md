---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:10:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777392277 64
1777392282 64
1777392287 64
1777392292 64
1777392297 64
1777392302 64
1777392307 64
1777392312 64
1777392317 64
1777392322 64
1777392327 64
1777392332 64
1777392337 64
1777392342 64
1777392347 64
1777392352 64
1777392357 64
1777392362 64
1777392367 64
1777392372 64
```
</details>

---

