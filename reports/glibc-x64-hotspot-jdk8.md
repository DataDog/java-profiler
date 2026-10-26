---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-26 08:33:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 72-80 cores)</summary>

```
1793017739 80
1793017744 80
1793017749 80
1793017754 80
1793017759 80
1793017764 80
1793017769 72
1793017774 72
1793017779 72
1793017784 72
1793017789 72
1793017794 72
1793017799 72
1793017804 72
1793017809 72
1793017814 72
1793017819 72
1793017824 72
1793017829 72
1793017834 72
```
</details>

---

