---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 05:50:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 7 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1786096046 31
1786096051 31
1786096056 26
1786096061 26
1786096066 27
1786096071 27
1786096076 27
1786096081 27
1786096086 27
1786096091 27
1786096096 27
1786096101 27
1786096106 27
1786096111 27
1786096116 27
1786096121 27
1786096126 27
1786096131 27
1786096136 27
1786096141 27
```
</details>

---

