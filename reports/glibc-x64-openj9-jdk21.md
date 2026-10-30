---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:38:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1793367223 76
1793367228 76
1793367233 76
1793367238 76
1793367243 76
1793367248 76
1793367253 76
1793367258 76
1793367263 76
1793367268 76
1793367273 76
1793367278 72
1793367283 72
1793367288 72
1793367293 72
1793367299 72
1793367304 72
1793367309 72
1793367314 72
1793367319 75
```
</details>

---

