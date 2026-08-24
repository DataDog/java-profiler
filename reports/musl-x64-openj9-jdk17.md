---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-24 09:28:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787577838 94
1787577843 94
1787577848 94
1787577853 94
1787577858 94
1787577863 94
1787577868 94
1787577873 94
1787577878 94
1787577883 94
1787577888 94
1787577893 96
1787577898 96
1787577903 96
1787577908 96
1787577913 96
1787577918 96
1787577923 96
1787577928 96
1787577933 96
```
</details>

---

