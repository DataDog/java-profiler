---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 09:53:39 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 43-64 cores)</summary>

```
1795618029 43
1795618034 43
1795618039 43
1795618044 43
1795618049 43
1795618054 64
1795618059 64
1795618064 64
1795618069 64
1795618074 64
1795618079 64
1795618084 64
1795618089 64
1795618094 64
1795618099 64
1795618104 64
1795618109 64
1795618114 64
1795618119 64
1795618124 64
```
</details>

---

