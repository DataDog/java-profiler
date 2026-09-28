---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-28 07:58:53 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790596437 40
1790596442 40
1790596447 40
1790596452 40
1790596457 40
1790596462 40
1790596467 40
1790596472 40
1790596477 40
1790596482 40
1790596487 40
1790596492 40
1790596497 40
1790596502 40
1790596507 40
1790596512 40
1790596517 40
1790596522 40
1790596527 40
1790596532 40
```
</details>

---

