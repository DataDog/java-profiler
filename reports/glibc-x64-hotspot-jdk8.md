---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-29 12:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-60 cores)</summary>

```
1793291827 60
1793291832 60
1793291837 60
1793291842 59
1793291847 59
1793291852 59
1793291857 59
1793291862 59
1793291867 59
1793291872 59
1793291877 59
1793291882 59
1793291887 59
1793291892 59
1793291897 59
1793291902 59
1793291907 59
1793291912 59
1793291917 59
1793291922 59
```
</details>

---

