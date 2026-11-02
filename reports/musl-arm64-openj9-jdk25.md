---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 14:28:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793647445 40
1793647450 40
1793647455 40
1793647460 40
1793647465 40
1793647470 40
1793647475 40
1793647480 40
1793647485 40
1793647490 40
1793647495 40
1793647500 40
1793647505 40
1793647510 40
1793647515 40
1793647520 40
1793647525 40
1793647530 40
1793647535 40
1793647540 40
```
</details>

---

