---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 08:48:50 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 53-63 cores)</summary>

```
1786452220 63
1786452225 63
1786452230 63
1786452235 55
1786452240 55
1786452245 55
1786452250 55
1786452255 55
1786452260 55
1786452265 55
1786452270 55
1786452275 55
1786452280 55
1786452285 55
1786452290 55
1786452295 55
1786452300 55
1786452305 55
1786452310 55
1786452315 55
```
</details>

---

