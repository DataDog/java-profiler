---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:43:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 63-66 cores)</summary>

```
1793187392 66
1793187397 66
1793187402 66
1793187407 66
1793187412 66
1793187417 66
1793187422 66
1793187427 66
1793187432 66
1793187437 63
1793187442 63
1793187447 63
1793187452 63
1793187457 63
1793187462 63
1793187467 63
1793187472 63
1793187477 63
1793187482 63
1793187488 63
```
</details>

---

