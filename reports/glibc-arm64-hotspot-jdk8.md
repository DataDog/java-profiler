---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-11 07:16:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786446606 53
1786446611 53
1786446616 53
1786446621 53
1786446626 53
1786446631 53
1786446636 53
1786446641 53
1786446646 53
1786446651 53
1786446656 53
1786446661 48
1786446667 48
1786446672 48
1786446677 48
1786446682 48
1786446687 48
1786446692 48
1786446697 48
1786446702 53
```
</details>

---

