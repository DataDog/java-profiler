---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:05:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1795449494 59
1795449499 59
1795449504 59
1795449509 59
1795449514 59
1795449519 59
1795449524 59
1795449529 59
1795449534 59
1795449539 59
1795449544 59
1795449549 59
1795449554 59
1795449559 59
1795449564 59
1795449569 59
1795449574 59
1795449579 59
1795449584 59
1795449589 59
```
</details>

---

