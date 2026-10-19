---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-18 21:25:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 41-63 cores)</summary>

```
1792372814 42
1792372819 42
1792372824 42
1792372829 42
1792372834 42
1792372839 63
1792372844 63
1792372849 43
1792372854 43
1792372859 43
1792372864 43
1792372869 41
1792372874 41
1792372879 41
1792372884 41
1792372889 41
1792372894 41
1792372899 41
1792372904 41
1792372910 41
```
</details>

---

