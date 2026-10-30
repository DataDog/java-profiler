---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 07:23:32 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1793359127 46
1793359132 46
1793359137 46
1793359142 46
1793359147 48
1793359152 48
1793359157 48
1793359162 48
1793359167 48
1793359172 48
1793359177 45
1793359182 45
1793359187 45
1793359192 45
1793359197 45
1793359202 45
1793359207 45
1793359212 45
1793359217 45
1793359222 45
```
</details>

---

