---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 07:24:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792408793 32
1792408798 32
1792408803 32
1792408808 32
1792408813 32
1792408818 32
1792408823 30
1792408828 30
1792408833 30
1792408838 30
1792408843 30
1792408848 30
1792408853 30
1792408858 30
1792408863 30
1792408868 30
1792408873 30
1792408878 30
1792408883 30
1792408888 30
```
</details>

---

