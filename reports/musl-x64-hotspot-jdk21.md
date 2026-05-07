---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:41:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 994 |
| Sample Rate | 16.57/sec |
| Health Score | 1036% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 78-86 cores)</summary>

```
1778171828 86
1778171833 86
1778171838 86
1778171843 86
1778171848 86
1778171853 86
1778171858 81
1778171863 81
1778171868 81
1778171873 81
1778171878 81
1778171883 81
1778171888 81
1778171893 81
1778171898 78
1778171903 78
1778171908 78
1778171913 78
1778171918 78
1778171923 78
```
</details>

---

