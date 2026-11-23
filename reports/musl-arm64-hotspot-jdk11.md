---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 10:10:51 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795446227 64
1795446232 64
1795446237 64
1795446242 64
1795446247 64
1795446252 64
1795446257 64
1795446262 64
1795446267 64
1795446272 64
1795446277 64
1795446282 64
1795446287 64
1795446292 64
1795446297 64
1795446302 64
1795446307 64
1795446312 64
1795446317 64
1795446322 64
```
</details>

---

