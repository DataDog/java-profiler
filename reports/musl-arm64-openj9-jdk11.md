---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 12:45:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1794937205 14
1794937210 14
1794937215 34
1794937220 34
1794937225 34
1794937230 34
1794937235 34
1794937240 34
1794937245 34
1794937250 34
1794937255 34
1794937260 34
1794937265 34
1794937270 34
1794937275 34
1794937280 34
1794937285 34
1794937290 34
1794937295 34
1794937300 34
```
</details>

---

