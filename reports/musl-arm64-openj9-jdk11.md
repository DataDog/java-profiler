---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:42:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (5 unique values: 50-60 cores)</summary>

```
1795538282 55
1795538287 55
1795538292 55
1795538297 60
1795538302 60
1795538307 60
1795538312 50
1795538317 50
1795538322 50
1795538327 50
1795538332 50
1795538337 50
1795538342 50
1795538347 50
1795538352 50
1795538357 50
1795538362 50
1795538367 50
1795538372 50
1795538377 50
```
</details>

---

