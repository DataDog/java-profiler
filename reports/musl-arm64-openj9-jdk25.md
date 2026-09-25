---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 06:34:10 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790332035 44
1790332040 43
1790332045 43
1790332050 43
1790332055 43
1790332060 43
1790332065 43
1790332070 43
1790332075 43
1790332080 44
1790332085 44
1790332090 44
1790332095 44
1790332100 44
1790332105 44
1790332110 44
1790332115 48
1790332120 48
1790332125 48
1790332130 48
```
</details>

---

