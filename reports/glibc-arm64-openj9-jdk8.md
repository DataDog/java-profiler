---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 05:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795517186 48
1795517191 48
1795517196 48
1795517201 48
1795517206 48
1795517211 48
1795517216 48
1795517221 48
1795517226 48
1795517231 48
1795517236 48
1795517241 48
1795517246 48
1795517251 48
1795517256 48
1795517261 64
1795517266 64
1795517271 64
1795517276 64
1795517281 64
```
</details>

---

