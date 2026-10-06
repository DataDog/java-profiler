---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 13:09:34 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791306307 40
1791306312 40
1791306317 40
1791306322 40
1791306327 40
1791306332 40
1791306337 40
1791306342 40
1791306347 40
1791306352 40
1791306357 40
1791306362 40
1791306367 40
1791306372 40
1791306377 40
1791306382 40
1791306387 40
1791306392 40
1791306397 40
1791306402 40
```
</details>

---

