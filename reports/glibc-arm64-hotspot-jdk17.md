---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 10:44:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 17-60 cores)</summary>

```
1790087762 17
1790087767 22
1790087772 22
1790087777 22
1790087782 22
1790087787 22
1790087792 22
1790087797 22
1790087802 22
1790087807 22
1790087812 22
1790087817 22
1790087822 22
1790087827 22
1790087832 22
1790087837 22
1790087842 22
1790087847 22
1790087852 22
1790087857 22
```
</details>

---

