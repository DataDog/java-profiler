---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 11:49:13 EST

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
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (4 unique values: 33-38 cores)</summary>

```
1794501709 38
1794501714 38
1794501719 38
1794501724 38
1794501729 38
1794501734 38
1794501739 38
1794501744 38
1794501749 38
1794501754 38
1794501759 38
1794501764 38
1794501769 38
1794501774 36
1794501779 36
1794501784 35
1794501789 35
1794501794 35
1794501799 35
1794501804 35
```
</details>

---

