---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 19:11:12 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794787549 32
1794787554 32
1794787559 32
1794787564 32
1794787569 32
1794787574 32
1794787579 32
1794787584 32
1794787589 32
1794787594 32
1794787599 32
1794787604 32
1794787609 32
1794787614 32
1794787619 32
1794787624 32
1794787629 32
1794787634 32
1794787639 32
1794787644 32
```
</details>

---

