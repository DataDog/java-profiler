---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:27:47 EDT

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (4 unique values: 33-38 cores)</summary>

```
1789737684 33
1789737689 33
1789737694 33
1789737699 33
1789737704 33
1789737709 33
1789737714 33
1789737719 33
1789737724 33
1789737729 33
1789737734 37
1789737739 37
1789737744 35
1789737749 35
1789737754 38
1789737759 38
1789737764 38
1789737769 38
1789737774 38
1789737779 38
```
</details>

---

