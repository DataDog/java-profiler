---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 10:30:05 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 47-79 cores)</summary>

```
1789655081 47
1789655086 49
1789655091 49
1789655096 49
1789655101 49
1789655106 49
1789655111 49
1789655116 49
1789655121 49
1789655126 49
1789655131 47
1789655136 47
1789655141 68
1789655146 68
1789655151 60
1789655156 60
1789655161 79
1789655166 79
1789655171 79
1789655176 79
```
</details>

---

