---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 19:11:11 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 11 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794787514 43
1794787519 43
1794787524 43
1794787529 43
1794787534 43
1794787539 43
1794787544 43
1794787549 43
1794787554 48
1794787559 48
1794787564 48
1794787569 48
1794787574 48
1794787579 48
1794787584 48
1794787589 48
1794787594 48
1794787599 48
1794787604 48
1794787609 48
```
</details>

---

