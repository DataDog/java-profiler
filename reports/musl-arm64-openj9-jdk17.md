---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 07:24:41 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 29-49 cores)</summary>

```
1792408788 43
1792408793 49
1792408798 49
1792408803 49
1792408808 49
1792408813 49
1792408818 49
1792408823 49
1792408828 49
1792408833 49
1792408838 49
1792408843 49
1792408848 49
1792408853 29
1792408858 29
1792408863 40
1792408868 40
1792408873 40
1792408878 40
1792408883 40
```
</details>

---

