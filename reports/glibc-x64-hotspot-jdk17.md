---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 11:53:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1793288662 23
1793288667 23
1793288672 23
1793288677 23
1793288682 23
1793288687 23
1793288692 23
1793288697 23
1793288702 23
1793288707 23
1793288712 32
1793288717 32
1793288722 32
1793288727 32
1793288732 32
1793288737 32
1793288742 32
1793288747 32
1793288752 32
1793288757 32
```
</details>

---

