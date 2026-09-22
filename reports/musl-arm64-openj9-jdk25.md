---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:28:37 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 27-64 cores)</summary>

```
1790094059 27
1790094064 27
1790094069 64
1790094074 64
1790094079 64
1790094084 64
1790094089 64
1790094094 64
1790094099 64
1790094104 64
1790094109 64
1790094114 64
1790094119 64
1790094124 64
1790094129 64
1790094134 64
1790094139 64
1790094144 64
1790094149 64
1790094154 64
```
</details>

---

