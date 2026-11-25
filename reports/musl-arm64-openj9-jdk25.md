---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 11:43:21 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795624640 47
1795624645 47
1795624650 47
1795624655 64
1795624660 64
1795624665 64
1795624670 64
1795624675 64
1795624680 64
1795624685 64
1795624690 47
1795624695 47
1795624700 47
1795624705 47
1795624710 47
1795624715 47
1795624720 47
1795624725 47
1795624730 47
1795624735 47
```
</details>

---

