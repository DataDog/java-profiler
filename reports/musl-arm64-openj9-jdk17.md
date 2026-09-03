---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 00:57:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 10 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1788411199 22
1788411204 24
1788411209 24
1788411214 24
1788411219 24
1788411224 24
1788411229 24
1788411234 24
1788411239 24
1788411244 24
1788411249 24
1788411254 24
1788411259 24
1788411264 24
1788411269 24
1788411274 24
1788411279 24
1788411284 24
1788411289 24
1788411294 19
```
</details>

---

