---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:56:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 65-72 cores)</summary>

```
1795434728 72
1795434733 72
1795434738 72
1795434743 72
1795434748 72
1795434753 72
1795434758 67
1795434763 67
1795434768 67
1795434774 67
1795434779 67
1795434784 67
1795434789 67
1795434794 67
1795434799 67
1795434804 67
1795434809 67
1795434814 67
1795434819 67
1795434824 67
```
</details>

---

