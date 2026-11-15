---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 08:56:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 11 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794750754 32
1794750759 32
1794750764 32
1794750769 32
1794750774 32
1794750779 32
1794750784 32
1794750789 32
1794750794 32
1794750799 32
1794750804 32
1794750809 32
1794750814 32
1794750819 32
1794750824 32
1794750829 32
1794750834 32
1794750839 32
1794750844 32
1794750849 32
```
</details>

---

