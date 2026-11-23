---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 20:31:40 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 13 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (2 unique values: 11-16 cores)</summary>

```
1795397183 16
1795397188 16
1795397193 16
1795397198 16
1795397203 16
1795397208 16
1795397213 16
1795397218 16
1795397223 16
1795397228 16
1795397233 16
1795397238 16
1795397243 16
1795397248 16
1795397253 16
1795397258 16
1795397263 16
1795397268 11
1795397273 11
1795397278 11
```
</details>

---

