---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:28:00 EST

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
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 10 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (3 unique values: 16-18 cores)</summary>

```
1795627373 16
1795627378 16
1795627383 16
1795627388 16
1795627393 16
1795627398 16
1795627403 18
1795627408 18
1795627413 18
1795627418 18
1795627423 18
1795627428 18
1795627433 18
1795627438 18
1795627443 18
1795627448 18
1795627453 18
1795627458 18
1795627463 18
1795627468 18
```
</details>

---

