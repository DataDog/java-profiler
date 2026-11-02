---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 14:28:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1793647412 48
1793647417 48
1793647422 48
1793647427 48
1793647432 48
1793647437 48
1793647442 48
1793647447 48
1793647452 48
1793647457 48
1793647462 48
1793647467 48
1793647472 48
1793647477 48
1793647482 48
1793647487 48
1793647492 48
1793647497 48
1793647502 48
1793647507 48
```
</details>

---

