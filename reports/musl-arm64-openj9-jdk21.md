---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:21:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 12 |
| Allocations | 196 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 38-50 cores)</summary>

```
1795195012 38
1795195017 38
1795195022 50
1795195027 50
1795195032 50
1795195037 50
1795195042 50
1795195047 50
1795195052 50
1795195057 50
1795195062 50
1795195067 50
1795195073 50
1795195078 50
1795195083 50
1795195088 50
1795195093 50
1795195098 50
1795195103 50
1795195108 50
```
</details>

---

