---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 16:50:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 12 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1789677813 17
1789677818 17
1789677823 17
1789677828 12
1789677833 12
1789677838 12
1789677843 12
1789677848 12
1789677853 12
1789677858 12
1789677863 12
1789677868 12
1789677873 12
1789677878 12
1789677883 12
1789677888 12
1789677893 12
1789677898 12
1789677903 12
1789677908 17
```
</details>

---

