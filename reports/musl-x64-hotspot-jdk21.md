---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:23:14 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 911 |
| Sample Rate | 15.18/sec |
| Health Score | 949% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 48-66 cores)</summary>

```
1778512702 66
1778512707 48
1778512712 48
1778512717 48
1778512722 53
1778512727 53
1778512732 53
1778512737 53
1778512742 53
1778512747 53
1778512752 53
1778512757 53
1778512762 53
1778512767 53
1778512772 53
1778512777 53
1778512782 58
1778512787 58
1778512792 58
1778512797 58
```
</details>

---

