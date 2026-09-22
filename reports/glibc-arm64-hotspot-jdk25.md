---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 10:44:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 13 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1790087802 40
1790087807 40
1790087812 40
1790087817 40
1790087822 40
1790087827 40
1790087832 40
1790087837 40
1790087842 40
1790087847 40
1790087852 40
1790087857 40
1790087862 42
1790087867 42
1790087872 42
1790087877 42
1790087882 42
1790087887 42
1790087892 42
1790087897 42
```
</details>

---

