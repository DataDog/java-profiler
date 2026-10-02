---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-02 12:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (6 unique values: 31-49 cores)</summary>

```
1790956744 33
1790956749 38
1790956754 38
1790956759 38
1790956764 38
1790956769 49
1790956774 49
1790956779 36
1790956784 36
1790956789 48
1790956794 48
1790956799 48
1790956804 48
1790956809 48
1790956814 31
1790956819 31
1790956824 31
1790956829 31
1790956834 31
1790956839 31
```
</details>

---

