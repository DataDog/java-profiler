---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 03:26:26 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791789759 32
1791789764 32
1791789769 32
1791789774 32
1791789779 32
1791789784 32
1791789789 32
1791789794 32
1791789799 32
1791789804 32
1791789809 32
1791789814 32
1791789819 32
1791789824 32
1791789829 32
1791789834 32
1791789839 32
1791789844 32
1791789849 32
1791789854 32
```
</details>

---

