---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-07 12:41:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-55 cores)</summary>

```
1778171833 40
1778171838 40
1778171843 40
1778171848 40
1778171853 40
1778171858 40
1778171863 40
1778171868 40
1778171873 40
1778171878 50
1778171883 50
1778171888 50
1778171893 50
1778171898 50
1778171903 50
1778171908 50
1778171913 50
1778171918 50
1778171923 50
1778171928 55
```
</details>

---

