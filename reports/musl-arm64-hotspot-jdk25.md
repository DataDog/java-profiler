---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 18:56:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (4 unique values: 28-40 cores)</summary>

```
1794268242 28
1794268247 28
1794268252 28
1794268257 28
1794268262 28
1794268267 28
1794268272 28
1794268277 28
1794268282 28
1794268287 28
1794268292 28
1794268297 28
1794268302 28
1794268307 28
1794268312 28
1794268317 28
1794268322 28
1794268327 32
1794268332 32
1794268337 32
```
</details>

---

