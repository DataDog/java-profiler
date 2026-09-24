---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 38-64 cores)</summary>

```
1790238302 64
1790238307 64
1790238312 64
1790238317 64
1790238322 40
1790238327 40
1790238332 40
1790238337 40
1790238342 40
1790238347 40
1790238352 40
1790238357 38
1790238362 38
1790238367 38
1790238372 38
1790238377 38
1790238382 38
1790238387 38
1790238392 38
1790238397 40
```
</details>

---

