---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:39:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1794328314 48
1794328319 48
1794328324 48
1794328329 48
1794328334 48
1794328339 48
1794328344 48
1794328349 48
1794328354 48
1794328359 48
1794328364 48
1794328369 48
1794328374 48
1794328379 48
1794328384 48
1794328389 48
1794328394 48
1794328399 47
1794328404 47
1794328409 47
```
</details>

---

