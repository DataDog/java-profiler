---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-02 12:03:18 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 36-41 cores)</summary>

```
1790956729 38
1790956734 38
1790956739 38
1790956744 36
1790956749 36
1790956754 36
1790956759 36
1790956764 36
1790956769 41
1790956774 41
1790956779 41
1790956784 41
1790956789 41
1790956794 41
1790956799 41
1790956804 41
1790956809 41
1790956814 41
1790956819 41
1790956824 41
```
</details>

---

