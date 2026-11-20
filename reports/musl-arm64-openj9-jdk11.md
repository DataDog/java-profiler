---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 14:01:22 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 8 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 29-49 cores)</summary>

```
1795200976 29
1795200981 29
1795200987 29
1795200992 29
1795200997 29
1795201002 29
1795201007 29
1795201012 29
1795201017 29
1795201022 29
1795201027 29
1795201032 29
1795201037 29
1795201042 49
1795201047 49
1795201052 49
1795201057 49
1795201062 49
1795201067 49
1795201072 49
```
</details>

---

