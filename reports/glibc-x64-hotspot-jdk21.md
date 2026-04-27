---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-27 14:05:02 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (6 unique values: 59-69 cores)</summary>

```
1777312782 68
1777312787 68
1777312792 63
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
```
</details>

---

