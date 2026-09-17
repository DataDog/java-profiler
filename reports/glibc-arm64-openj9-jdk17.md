---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:50:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1789677802 12
1789677807 12
1789677812 12
1789677817 12
1789677822 12
1789677827 12
1789677832 12
1789677837 12
1789677842 17
1789677847 17
1789677852 17
1789677857 17
1789677862 17
1789677867 17
1789677872 17
1789677877 17
1789677882 17
1789677887 17
1789677892 17
1789677897 17
```
</details>

---

