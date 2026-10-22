---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:01:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 63-68 cores)</summary>

```
1792670186 67
1792670191 67
1792670196 67
1792670201 67
1792670206 67
1792670211 67
1792670216 65
1792670221 65
1792670226 63
1792670231 63
1792670236 63
1792670241 63
1792670246 63
1792670251 63
1792670256 65
1792670261 65
1792670266 65
1792670271 65
1792670276 65
1792670281 65
```
</details>

---

