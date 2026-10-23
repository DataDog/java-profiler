---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 08:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 10 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 14 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1792759897 41
1792759902 41
1792759907 41
1792759912 41
1792759917 41
1792759922 41
1792759927 41
1792759932 41
1792759937 43
1792759942 43
1792759947 43
1792759952 43
1792759957 43
1792759962 43
1792759967 48
1792759972 48
1792759977 48
1792759982 48
1792759987 48
1792759992 48
```
</details>

---

