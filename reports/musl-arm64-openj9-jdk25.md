---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 05:56:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1794739937 21
1794739942 21
1794739947 21
1794739952 21
1794739957 21
1794739962 21
1794739967 21
1794739972 21
1794739977 21
1794739982 21
1794739987 21
1794739992 21
1794739997 21
1794740002 21
1794740007 21
1794740012 21
1794740017 21
1794740022 21
1794740027 21
1794740032 21
```
</details>

---

