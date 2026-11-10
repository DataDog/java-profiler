---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 06:59:42 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 11 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (4 unique values: 42-51 cores)</summary>

```
1794311738 43
1794311743 43
1794311748 42
1794311753 42
1794311758 42
1794311763 42
1794311768 42
1794311773 42
1794311778 46
1794311783 46
1794311788 46
1794311793 46
1794311798 46
1794311803 46
1794311808 46
1794311813 46
1794311818 46
1794311823 46
1794311828 46
1794311833 46
```
</details>

---

