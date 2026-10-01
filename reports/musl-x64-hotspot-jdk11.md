---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 11:00:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 24-27 cores)</summary>

```
1790866574 26
1790866579 26
1790866584 26
1790866589 26
1790866594 26
1790866599 24
1790866604 24
1790866609 24
1790866614 24
1790866619 24
1790866624 24
1790866629 27
1790866634 27
1790866639 27
1790866644 27
1790866649 27
1790866654 27
1790866659 27
1790866664 27
1790866669 27
```
</details>

---

