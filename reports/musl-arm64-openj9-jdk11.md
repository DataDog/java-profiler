---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:34:10 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 13 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790332045 50
1790332050 50
1790332055 50
1790332060 50
1790332065 50
1790332070 50
1790332075 50
1790332080 50
1790332085 50
1790332090 50
1790332095 50
1790332100 50
1790332105 50
1790332110 50
1790332115 50
1790332120 50
1790332125 50
1790332130 50
1790332135 50
1790332140 50
```
</details>

---

