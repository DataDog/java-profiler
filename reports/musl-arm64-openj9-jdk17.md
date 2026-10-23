---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 16:41:00 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792787768 43
1792787773 43
1792787778 43
1792787783 43
1792787788 43
1792787793 43
1792787798 43
1792787803 43
1792787808 48
1792787813 48
1792787818 48
1792787823 48
1792787828 43
1792787833 43
1792787838 43
1792787843 43
1792787848 43
1792787853 43
1792787858 43
1792787863 43
```
</details>

---

