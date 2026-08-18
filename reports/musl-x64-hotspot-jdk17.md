---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 21:38:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1787016882 79
1787016887 79
1787016892 79
1787016897 79
1787016902 96
1787016907 96
1787016912 96
1787016917 96
1787016922 96
1787016927 96
1787016932 96
1787016937 96
1787016942 96
1787016947 96
1787016952 96
1787016957 96
1787016962 96
1787016967 96
1787016972 96
1787016977 96
```
</details>

---

