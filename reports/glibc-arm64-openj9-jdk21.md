---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-15 03:56:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 23-53 cores)</summary>

```
1792050803 53
1792050808 53
1792050813 53
1792050818 53
1792050823 28
1792050828 28
1792050833 23
1792050838 23
1792050843 23
1792050848 23
1792050853 23
1792050858 23
1792050863 23
1792050868 23
1792050873 23
1792050878 23
1792050883 23
1792050888 23
1792050893 23
1792050898 23
```
</details>

---

