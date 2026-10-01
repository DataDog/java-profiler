---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 11:00:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790866569 43
1790866574 43
1790866579 43
1790866584 43
1790866589 43
1790866594 43
1790866599 43
1790866604 43
1790866609 43
1790866614 48
1790866619 48
1790866624 43
1790866629 43
1790866634 43
1790866639 43
1790866644 43
1790866649 43
1790866654 43
1790866659 43
1790866664 43
```
</details>

---

