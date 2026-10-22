---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:01:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 63-68 cores)</summary>

```
1792670200 65
1792670205 65
1792670210 65
1792670215 65
1792670220 65
1792670225 63
1792670230 63
1792670235 63
1792670240 63
1792670245 63
1792670250 63
1792670255 65
1792670260 65
1792670265 65
1792670270 65
1792670275 65
1792670280 65
1792670285 65
1792670290 65
1792670295 65
```
</details>

---

