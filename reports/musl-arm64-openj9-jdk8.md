---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-07 07:29:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1791372329 24
1791372334 24
1791372340 24
1791372345 24
1791372350 24
1791372355 24
1791372360 24
1791372365 24
1791372370 24
1791372375 24
1791372380 24
1791372385 24
1791372390 24
1791372395 24
1791372400 24
1791372405 24
1791372410 24
1791372415 24
1791372420 32
1791372425 32
```
</details>

---

