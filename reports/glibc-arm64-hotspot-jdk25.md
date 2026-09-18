---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 02:31:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 14 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789712786 48
1789712791 48
1789712796 48
1789712801 48
1789712806 48
1789712811 48
1789712816 48
1789712821 48
1789712826 48
1789712831 48
1789712836 48
1789712841 48
1789712846 48
1789712851 48
1789712856 48
1789712861 48
1789712866 48
1789712871 48
1789712876 48
1789712881 48
```
</details>

---

