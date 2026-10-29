---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 12:44:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 92 |
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
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 77-92 cores)</summary>

```
1793291817 77
1793291822 77
1793291827 77
1793291832 77
1793291837 77
1793291842 77
1793291847 77
1793291852 77
1793291857 77
1793291862 77
1793291867 77
1793291872 77
1793291877 77
1793291882 77
1793291887 77
1793291892 85
1793291897 85
1793291902 85
1793291907 85
1793291912 85
```
</details>

---

