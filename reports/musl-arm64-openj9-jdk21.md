---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:00:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
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
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793098436 40
1793098441 40
1793098446 40
1793098451 40
1793098456 40
1793098462 40
1793098467 40
1793098472 40
1793098477 40
1793098482 40
1793098487 40
1793098492 40
1793098497 40
1793098502 40
1793098507 40
1793098512 40
1793098517 40
1793098522 40
1793098527 40
1793098532 40
```
</details>

---

