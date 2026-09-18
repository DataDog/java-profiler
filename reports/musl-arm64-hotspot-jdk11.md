---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 9 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (6 unique values: 13-23 cores)</summary>

```
1789737709 21
1789737714 21
1789737719 21
1789737724 21
1789737729 21
1789737734 21
1789737739 23
1789737744 23
1789737749 17
1789737754 17
1789737759 17
1789737764 17
1789737769 17
1789737774 17
1789737779 17
1789737784 16
1789737789 16
1789737794 16
1789737799 16
1789737804 13
```
</details>

---

