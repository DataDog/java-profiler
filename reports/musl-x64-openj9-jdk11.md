---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:06:32 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 56-63 cores)</summary>

```
1794430817 63
1794430822 63
1794430827 63
1794430832 63
1794430837 63
1794430842 61
1794430847 61
1794430852 61
1794430857 58
1794430862 58
1794430867 56
1794430872 56
1794430877 56
1794430882 56
1794430887 56
1794430892 56
1794430897 56
1794430902 56
1794430907 56
1794430912 56
```
</details>

---

