---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-12 08:04:10 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 11 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 39-45 cores)</summary>

```
1791806393 45
1791806398 45
1791806403 45
1791806408 45
1791806413 43
1791806418 43
1791806423 43
1791806428 43
1791806433 43
1791806438 43
1791806443 43
1791806448 43
1791806453 41
1791806458 41
1791806463 41
1791806468 39
1791806473 39
1791806478 39
1791806483 39
1791806488 39
```
</details>

---

