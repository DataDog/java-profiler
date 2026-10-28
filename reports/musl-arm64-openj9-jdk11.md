---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 06:30:18 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1793183054 47
1793183059 45
1793183064 45
1793183069 45
1793183074 45
1793183079 46
1793183084 46
1793183089 46
1793183094 46
1793183099 46
1793183104 46
1793183109 46
1793183114 46
1793183119 46
1793183124 46
1793183129 46
1793183134 46
1793183139 48
1793183144 48
1793183149 48
```
</details>

---

