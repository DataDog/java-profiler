---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:48:35 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 15 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (5 unique values: 35-64 cores)</summary>

```
1795027359 64
1795027364 64
1795027369 64
1795027374 63
1795027379 63
1795027384 63
1795027389 63
1795027394 63
1795027399 63
1795027404 63
1795027409 63
1795027414 63
1795027419 63
1795027424 63
1795027429 63
1795027434 48
1795027439 48
1795027445 48
1795027450 48
1795027455 48
```
</details>

---

