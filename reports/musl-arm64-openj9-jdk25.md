---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 19:06:21 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 12 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (3 unique values: 32-64 cores)</summary>

```
1793142080 32
1793142085 32
1793142090 32
1793142095 34
1793142100 34
1793142105 34
1793142110 34
1793142115 34
1793142120 34
1793142125 34
1793142130 34
1793142135 64
1793142140 64
1793142145 64
1793142150 64
1793142155 64
1793142160 64
1793142165 64
1793142170 64
1793142175 64
```
</details>

---

