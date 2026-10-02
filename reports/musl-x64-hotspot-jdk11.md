---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-02 12:03:20 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 47-96 cores)</summary>

```
1790956704 47
1790956709 47
1790956714 47
1790956719 47
1790956724 47
1790956729 47
1790956734 47
1790956739 47
1790956744 47
1790956749 47
1790956754 50
1790956759 50
1790956764 50
1790956769 70
1790956774 70
1790956779 70
1790956784 70
1790956789 70
1790956794 70
1790956799 70
```
</details>

---

