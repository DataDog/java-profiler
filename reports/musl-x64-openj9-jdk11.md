---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:01:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (4 unique values: 24-32 cores)</summary>

```
1792670160 26
1792670166 26
1792670171 26
1792670176 26
1792670181 26
1792670186 26
1792670191 26
1792670196 26
1792670201 26
1792670206 26
1792670211 26
1792670216 26
1792670221 24
1792670226 24
1792670231 24
1792670236 24
1792670241 24
1792670246 24
1792670251 30
1792670256 30
```
</details>

---

