---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:50:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 38-45 cores)</summary>

```
1794933928 45
1794933933 45
1794933938 45
1794933943 45
1794933948 45
1794933953 45
1794933958 45
1794933963 38
1794933968 38
1794933973 38
1794933978 38
1794933983 38
1794933988 38
1794933993 38
1794933998 38
1794934003 38
1794934008 38
1794934013 38
1794934019 38
1794934024 38
```
</details>

---

