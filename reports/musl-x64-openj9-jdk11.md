---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 10:44:38 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 947 |
| Sample Rate | 15.78/sec |
| Health Score | 986% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1790087786 28
1790087791 28
1790087796 28
1790087801 28
1790087806 28
1790087811 28
1790087816 28
1790087821 28
1790087826 28
1790087831 28
1790087836 28
1790087841 28
1790087846 30
1790087851 30
1790087856 30
1790087861 30
1790087866 30
1790087871 30
1790087876 30
1790087881 30
```
</details>

---

