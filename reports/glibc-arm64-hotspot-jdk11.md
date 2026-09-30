---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:37:22 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1790771564 48
1790771569 48
1790771574 48
1790771579 48
1790771584 48
1790771589 48
1790771594 48
1790771599 48
1790771604 48
1790771609 48
1790771614 48
1790771619 48
1790771624 48
1790771629 38
1790771634 38
1790771639 38
1790771644 38
1790771649 38
1790771654 38
1790771659 38
```
</details>

---

