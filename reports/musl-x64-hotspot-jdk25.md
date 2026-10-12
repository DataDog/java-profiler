---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-12 05:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 66-86 cores)</summary>

```
1791798662 66
1791798667 66
1791798672 86
1791798677 86
1791798682 83
1791798687 83
1791798692 83
1791798697 83
1791798702 83
1791798707 83
1791798712 83
1791798717 85
1791798722 85
1791798727 85
1791798732 85
1791798737 85
1791798742 85
1791798747 85
1791798752 85
1791798757 85
```
</details>

---

