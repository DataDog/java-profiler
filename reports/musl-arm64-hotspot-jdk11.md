---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:21:57 EST

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
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795641271 34
1795641276 34
1795641281 29
1795641286 29
1795641291 29
1795641296 29
1795641301 29
1795641306 29
1795641311 29
1795641316 29
1795641321 29
1795641326 29
1795641331 29
1795641336 29
1795641341 34
1795641346 34
1795641351 34
1795641356 34
1795641361 34
1795641366 34
```
</details>

---

