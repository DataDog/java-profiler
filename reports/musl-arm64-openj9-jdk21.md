---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 08:48:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (4 unique values: 44-64 cores)</summary>

```
1786452217 53
1786452222 53
1786452227 48
1786452232 48
1786452237 48
1786452242 48
1786452247 48
1786452252 48
1786452257 48
1786452262 48
1786452267 48
1786452272 53
1786452277 53
1786452282 53
1786452287 53
1786452292 64
1786452297 64
1786452302 64
1786452307 64
1786452312 44
```
</details>

---

