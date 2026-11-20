---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 08:52:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 28-37 cores)</summary>

```
1795182297 30
1795182302 30
1795182307 30
1795182312 30
1795182317 30
1795182322 30
1795182327 30
1795182332 30
1795182337 28
1795182342 28
1795182347 28
1795182352 28
1795182357 28
1795182362 28
1795182367 28
1795182372 28
1795182377 28
1795182382 28
1795182387 28
1795182392 28
```
</details>

---

