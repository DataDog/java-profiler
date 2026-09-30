---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:19:12 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 947 |
| Sample Rate | 15.78/sec |
| Health Score | 986% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790763137 48
1790763142 48
1790763147 48
1790763152 48
1790763157 48
1790763162 48
1790763167 48
1790763172 48
1790763177 48
1790763182 48
1790763187 48
1790763192 48
1790763197 48
1790763202 48
1790763207 48
1790763212 48
1790763218 48
1790763223 48
1790763228 48
1790763233 48
```
</details>

---

