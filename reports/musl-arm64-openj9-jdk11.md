---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 16:21:38 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794950270 33
1794950275 33
1794950280 33
1794950285 33
1794950290 33
1794950295 33
1794950300 33
1794950305 38
1794950310 38
1794950315 38
1794950320 38
1794950325 38
1794950330 38
1794950335 38
1794950340 38
1794950345 38
1794950350 38
1794950355 38
1794950360 38
1794950365 38
```
</details>

---

