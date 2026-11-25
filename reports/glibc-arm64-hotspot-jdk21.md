---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:22:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795641363 28
1795641369 33
1795641374 33
1795641379 33
1795641384 33
1795641389 33
1795641394 33
1795641399 33
1795641404 33
1795641409 33
1795641414 33
1795641419 33
1795641424 33
1795641429 33
1795641434 33
1795641439 33
1795641444 33
1795641449 33
1795641454 33
1795641459 33
```
</details>

---

