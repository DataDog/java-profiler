---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 05:49:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 13 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 11 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1788342297 44
1788342302 44
1788342307 44
1788342312 44
1788342317 44
1788342322 44
1788342327 44
1788342332 44
1788342337 44
1788342342 44
1788342347 44
1788342352 44
1788342357 44
1788342362 44
1788342367 44
1788342372 44
1788342377 39
1788342382 39
1788342387 39
1788342392 39
```
</details>

---

