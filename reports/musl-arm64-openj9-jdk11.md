---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:33:16 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786454934 32
1786454939 32
1786454944 32
1786454949 32
1786454954 32
1786454959 32
1786454964 32
1786454969 32
1786454974 32
1786454979 32
1786454984 32
1786454989 32
1786454994 32
1786454999 32
1786455004 32
1786455009 32
1786455014 32
1786455019 32
1786455024 32
1786455029 32
```
</details>

---

