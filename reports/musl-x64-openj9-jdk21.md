---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 19:49:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 84-94 cores)</summary>

```
1794789903 94
1794789908 94
1794789913 94
1794789918 86
1794789923 86
1794789928 84
1794789933 84
1794789938 84
1794789943 84
1794789948 84
1794789953 84
1794789958 84
1794789963 84
1794789968 84
1794789973 84
1794789978 84
1794789983 84
1794789988 84
1794789993 84
1794789998 84
```
</details>

---

