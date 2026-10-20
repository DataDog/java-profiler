---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 07:02:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 7 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 38-46 cores)</summary>

```
1792493858 38
1792493863 38
1792493868 38
1792493873 38
1792493878 38
1792493883 38
1792493888 38
1792493893 38
1792493898 43
1792493903 43
1792493908 43
1792493913 43
1792493918 43
1792493923 43
1792493928 43
1792493933 43
1792493938 43
1792493943 43
1792493948 43
1792493953 43
```
</details>

---

