---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 09:26:39 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795702903 64
1795702908 64
1795702913 64
1795702918 64
1795702923 64
1795702928 64
1795702933 64
1795702938 64
1795702943 64
1795702948 64
1795702953 64
1795702958 64
1795702963 64
1795702968 64
1795702973 64
1795702978 64
1795702983 64
1795702988 64
1795702993 64
1795702998 64
```
</details>

---

