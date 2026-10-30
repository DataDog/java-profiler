---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 07:23:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1793359162 64
1793359167 64
1793359172 64
1793359177 64
1793359182 64
1793359187 66
1793359192 66
1793359197 66
1793359202 66
1793359207 66
1793359212 66
1793359217 64
1793359222 64
1793359227 64
1793359232 64
1793359237 64
1793359242 64
1793359247 64
1793359252 64
1793359257 64
```
</details>

---

