---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 14:05:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (6 unique values: 59-69 cores)</summary>

```
1777312787 68
1777312792 68
1777312797 63
1777312802 63
1777312807 59
1777312812 59
1777312817 59
1777312822 59
1777312827 59
1777312832 64
1777312837 64
1777312842 62
1777312847 62
1777312852 62
1777312857 62
1777312862 62
1777312867 62
1777312872 62
1777312877 69
1777312882 69
```
</details>

---

