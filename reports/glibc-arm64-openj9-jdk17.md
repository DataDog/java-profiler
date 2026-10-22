---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 19:06:01 EDT

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 7 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792710136 46
1792710141 46
1792710146 46
1792710151 46
1792710156 46
1792710161 46
1792710166 46
1792710171 46
1792710176 46
1792710181 46
1792710186 46
1792710191 46
1792710196 46
1792710201 46
1792710206 46
1792710211 51
1792710216 51
1792710221 51
1792710226 51
1792710231 51
```
</details>

---

