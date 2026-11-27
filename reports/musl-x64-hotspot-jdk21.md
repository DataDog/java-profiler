---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 08:39:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 59-88 cores)</summary>

```
1795786393 60
1795786398 88
1795786403 88
1795786408 88
1795786413 88
1795786418 60
1795786423 60
1795786428 60
1795786433 60
1795786438 60
1795786443 60
1795786448 60
1795786453 60
1795786458 60
1795786463 60
1795786468 60
1795786473 60
1795786478 60
1795786483 60
1795786488 60
```
</details>

---

