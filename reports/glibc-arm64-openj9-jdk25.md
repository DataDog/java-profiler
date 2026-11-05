---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 09:56:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 9 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 10 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793890217 32
1793890222 32
1793890227 32
1793890232 32
1793890237 32
1793890242 32
1793890247 32
1793890252 32
1793890257 32
1793890262 32
1793890267 32
1793890272 32
1793890277 32
1793890282 32
1793890287 32
1793890292 32
1793890297 32
1793890302 32
1793890307 32
1793890312 32
```
</details>

---

