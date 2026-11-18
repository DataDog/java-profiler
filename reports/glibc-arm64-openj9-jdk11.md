---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:43:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 8 |
| Allocations | 101 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 16-21 cores)</summary>

```
1794998160 16
1794998165 16
1794998170 16
1794998175 21
1794998180 21
1794998185 21
1794998190 21
1794998195 21
1794998200 21
1794998205 21
1794998210 21
1794998215 21
1794998220 21
1794998225 21
1794998230 21
1794998235 21
1794998240 21
1794998245 21
1794998250 21
1794998255 21
```
</details>

---

