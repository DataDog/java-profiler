---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 06:16:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 12 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1792145561 45
1792145566 48
1792145571 48
1792145576 48
1792145581 48
1792145586 48
1792145591 48
1792145596 48
1792145601 48
1792145606 48
1792145611 48
1792145616 48
1792145621 48
1792145626 48
1792145631 48
1792145636 48
1792145641 48
1792145646 48
1792145651 48
1792145656 48
```
</details>

---

