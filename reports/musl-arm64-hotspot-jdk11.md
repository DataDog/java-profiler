---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:49:36 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1793295788 48
1793295793 48
1793295798 48
1793295803 48
1793295808 48
1793295813 48
1793295818 48
1793295823 48
1793295828 48
1793295833 46
1793295838 46
1793295843 46
1793295848 46
1793295853 46
1793295858 46
1793295863 46
1793295868 46
1793295873 46
1793295878 46
1793295883 46
```
</details>

---

