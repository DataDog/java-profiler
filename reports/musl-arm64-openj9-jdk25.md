---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 08:56:21 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 17-24 cores)</summary>

```
1794750685 17
1794750690 17
1794750695 17
1794750700 17
1794750705 17
1794750710 17
1794750715 19
1794750720 19
1794750725 19
1794750730 19
1794750735 24
1794750741 24
1794750746 24
1794750751 24
1794750756 24
1794750761 24
1794750766 24
1794750771 24
1794750776 24
1794750781 24
```
</details>

---

