---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 10:08:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 77-85 cores)</summary>

```
1790690589 85
1790690594 85
1790690599 85
1790690604 85
1790690609 85
1790690614 77
1790690619 77
1790690624 77
1790690629 77
1790690634 77
1790690639 77
1790690644 77
1790690649 77
1790690654 77
1790690659 77
1790690664 77
1790690669 77
1790690674 77
1790690679 77
1790690684 80
```
</details>

---

