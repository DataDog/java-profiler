---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:53:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789677818 48
1789677823 43
1789677828 43
1789677833 43
1789677838 43
1789677843 43
1789677848 43
1789677853 43
1789677858 43
1789677863 43
1789677868 43
1789677873 43
1789677878 43
1789677883 43
1789677888 43
1789677893 43
1789677898 43
1789677903 43
1789677908 43
1789677913 48
```
</details>

---

