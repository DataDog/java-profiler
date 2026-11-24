---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 17:14:26 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 12 |
| Allocations | 197 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1795558212 48
1795558217 48
1795558222 48
1795558227 48
1795558232 48
1795558237 48
1795558242 48
1795558247 48
1795558252 48
1795558257 48
1795558262 48
1795558267 48
1795558272 48
1795558277 48
1795558282 48
1795558287 48
1795558292 48
1795558297 43
1795558302 43
1795558307 43
```
</details>

---

