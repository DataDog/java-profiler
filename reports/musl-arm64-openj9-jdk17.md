---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-15 05:56:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794739922 40
1794739927 40
1794739932 40
1794739937 40
1794739942 40
1794739947 40
1794739952 40
1794739957 40
1794739962 40
1794739967 40
1794739972 40
1794739977 40
1794739982 40
1794739987 40
1794739992 40
1794739997 40
1794740002 40
1794740007 40
1794740012 40
1794740017 40
```
</details>

---

