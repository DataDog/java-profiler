---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:47:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 14 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794480176 31
1794480181 31
1794480186 31
1794480191 31
1794480196 31
1794480201 31
1794480206 31
1794480211 31
1794480216 31
1794480221 31
1794480226 31
1794480231 36
1794480236 36
1794480241 36
1794480246 36
1794480251 36
1794480256 36
1794480261 36
1794480266 36
1794480271 36
```
</details>

---

