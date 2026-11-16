---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:22:08 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 14.55/sec |
| Health Score | 909% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 46-49 cores)</summary>

```
1794842230 46
1794842235 46
1794842240 46
1794842245 46
1794842250 46
1794842255 48
1794842260 48
1794842265 48
1794842270 48
1794842275 48
1794842280 48
1794842285 48
1794842290 48
1794842295 49
1794842300 49
1794842305 47
1794842310 47
1794842315 47
1794842320 47
1794842325 47
```
</details>

---

