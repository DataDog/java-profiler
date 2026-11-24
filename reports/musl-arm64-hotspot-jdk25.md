---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:42:51 EST

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
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795538262 28
1795538267 28
1795538272 28
1795538277 28
1795538282 28
1795538287 28
1795538292 28
1795538297 28
1795538302 28
1795538307 28
1795538312 28
1795538317 28
1795538322 28
1795538327 28
1795538332 33
1795538337 33
1795538342 33
1795538347 33
1795538352 33
1795538357 33
```
</details>

---

