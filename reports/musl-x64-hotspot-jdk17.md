---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 09:45:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (6 unique values: 66-96 cores)</summary>

```
1787664984 96
1787664989 96
1787664994 96
1787664999 96
1787665004 96
1787665009 96
1787665014 96
1787665019 96
1787665024 96
1787665029 96
1787665034 96
1787665039 96
1787665044 91
1787665049 91
1787665054 86
1787665059 86
1787665064 86
1787665069 76
1787665074 76
1787665079 76
```
</details>

---

