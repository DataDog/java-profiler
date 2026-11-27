---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 07:48:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 17-48 cores)</summary>

```
1795783417 17
1795783422 17
1795783427 17
1795783432 17
1795783437 17
1795783442 17
1795783447 17
1795783452 17
1795783457 17
1795783462 17
1795783467 48
1795783472 48
1795783477 48
1795783482 48
1795783487 48
1795783492 48
1795783497 48
1795783502 48
1795783507 48
1795783512 48
```
</details>

---

