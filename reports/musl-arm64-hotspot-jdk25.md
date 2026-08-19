---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 06:13:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 15 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (2 unique values: 40-52 cores)</summary>

```
1787134023 52
1787134028 52
1787134033 52
1787134038 52
1787134043 52
1787134048 52
1787134053 52
1787134058 52
1787134063 52
1787134068 52
1787134073 52
1787134078 52
1787134083 52
1787134088 52
1787134093 52
1787134098 52
1787134103 52
1787134108 52
1787134113 52
1787134118 52
```
</details>

---

