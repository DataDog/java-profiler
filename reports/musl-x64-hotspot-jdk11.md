---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 10:12:49 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1788530790 79
1788530795 79
1788530800 79
1788530805 79
1788530810 79
1788530815 79
1788530820 79
1788530825 81
1788530830 81
1788530835 81
1788530840 81
1788530845 81
1788530850 81
1788530855 81
1788530860 81
1788530865 81
1788530870 81
1788530875 81
1788530880 81
1788530885 81
```
</details>

---

