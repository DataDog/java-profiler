---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-05 09:56:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1793890200 55
1793890205 55
1793890210 55
1793890215 55
1793890220 55
1793890225 55
1793890230 55
1793890235 55
1793890240 55
1793890245 64
1793890250 64
1793890255 64
1793890260 64
1793890265 64
1793890270 64
1793890275 64
1793890280 64
1793890285 64
1793890290 62
1793890295 62
```
</details>

---

