---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 12:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1000 |
| Sample Rate | 16.67/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (4 unique values: 69-77 cores)</summary>

```
1793291857 77
1793291862 72
1793291867 72
1793291872 72
1793291877 72
1793291882 72
1793291887 72
1793291892 72
1793291897 72
1793291902 72
1793291907 72
1793291912 72
1793291917 72
1793291922 72
1793291927 72
1793291932 72
1793291937 72
1793291942 72
1793291947 69
1793291952 69
```
</details>

---

