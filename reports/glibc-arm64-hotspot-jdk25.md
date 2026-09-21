---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:57:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 18-33 cores)</summary>

```
1789998796 18
1789998801 18
1789998806 18
1789998811 18
1789998816 33
1789998821 33
1789998826 33
1789998831 33
1789998836 33
1789998841 33
1789998846 33
1789998851 33
1789998856 33
1789998861 33
1789998866 33
1789998871 33
1789998876 33
1789998881 33
1789998886 33
1789998891 33
```
</details>

---

