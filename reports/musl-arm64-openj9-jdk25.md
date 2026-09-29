---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 09:12:07 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 13 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1790687098 28
1790687103 28
1790687108 28
1790687113 28
1790687118 28
1790687123 28
1790687128 28
1790687133 28
1790687138 28
1790687143 28
1790687148 28
1790687153 28
1790687158 28
1790687163 48
1790687168 48
1790687173 48
1790687178 48
1790687183 28
1790687188 28
1790687193 28
```
</details>

---

