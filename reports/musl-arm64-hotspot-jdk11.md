---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 20:28:59 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1794792269 34
1794792274 34
1794792279 34
1794792284 34
1794792289 34
1794792294 32
1794792299 32
1794792304 32
1794792309 32
1794792314 32
1794792319 32
1794792324 32
1794792329 32
1794792334 32
1794792339 34
1794792344 34
1794792349 34
1794792354 34
1794792359 34
1794792364 34
```
</details>

---

