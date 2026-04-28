---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 12:10:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777392259 64
1777392264 64
1777392269 64
1777392274 64
1777392279 64
1777392284 64
1777392289 64
1777392294 64
1777392299 64
1777392304 64
1777392309 64
1777392314 64
1777392319 64
1777392324 64
1777392329 64
1777392334 64
1777392339 64
1777392344 64
1777392349 64
1777392354 64
```
</details>

---

