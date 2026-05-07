---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 12:41:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 10 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778171903 64
1778171908 64
1778171913 62
1778171918 62
1778171923 62
1778171928 62
1778171933 62
1778171938 62
1778171943 62
1778171948 62
1778171953 62
1778171958 62
1778171963 62
1778171968 62
1778171973 64
1778171978 64
1778171983 64
1778171988 64
1778171993 64
1778171998 64
```
</details>

---

