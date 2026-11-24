---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (3 unique values: 43-64 cores)</summary>

```
1795529738 43
1795529743 43
1795529748 43
1795529753 59
1795529758 59
1795529763 59
1795529768 59
1795529773 59
1795529778 59
1795529783 59
1795529788 59
1795529793 59
1795529798 59
1795529803 59
1795529808 59
1795529813 59
1795529818 64
1795529823 64
1795529828 64
1795529833 64
```
</details>

---

