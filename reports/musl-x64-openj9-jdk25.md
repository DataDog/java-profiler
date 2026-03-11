---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 16:37:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 984 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 13 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1773261127 30
1773261132 30
1773261137 30
1773261142 30
1773261147 30
1773261152 30
1773261157 30
1773261162 30
1773261167 30
1773261172 30
1773261177 30
1773261182 30
1773261187 28
1773261192 28
1773261197 28
1773261202 28
1773261207 28
1773261212 28
1773261217 28
1773261222 28
```
</details>

---

