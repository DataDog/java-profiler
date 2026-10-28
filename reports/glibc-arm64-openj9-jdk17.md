---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 06:30:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 13 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793183141 46
1793183146 46
1793183151 46
1793183156 46
1793183161 46
1793183166 46
1793183171 46
1793183176 46
1793183181 46
1793183186 46
1793183191 51
1793183196 51
1793183201 51
1793183206 51
1793183211 51
1793183216 51
1793183221 51
1793183226 51
1793183231 51
1793183236 51
```
</details>

---

