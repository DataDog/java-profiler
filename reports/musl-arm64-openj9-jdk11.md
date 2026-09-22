---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 17:00:43 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 10 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1790110480 44
1790110485 44
1790110490 44
1790110495 44
1790110500 49
1790110505 49
1790110510 49
1790110515 49
1790110520 49
1790110525 49
1790110530 49
1790110535 49
1790110540 49
1790110545 49
1790110550 49
1790110555 49
1790110560 49
1790110565 49
1790110570 49
1790110575 49
```
</details>

---

