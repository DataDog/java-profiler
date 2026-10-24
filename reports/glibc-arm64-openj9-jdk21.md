---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:16:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 7 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 40-43 cores)</summary>

```
1792833208 40
1792833213 42
1792833218 42
1792833223 42
1792833228 42
1792833233 42
1792833238 42
1792833243 41
1792833248 41
1792833253 41
1792833258 41
1792833263 41
1792833268 41
1792833273 41
1792833278 41
1792833283 41
1792833288 41
1792833293 41
1792833299 41
1792833304 41
```
</details>

---

