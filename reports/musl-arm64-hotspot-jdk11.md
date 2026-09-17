---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:53:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 969 |
| Sample Rate | 16.15/sec |
| Health Score | 1009% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 30-64 cores)</summary>

```
1789677812 30
1789677817 30
1789677822 30
1789677827 30
1789677832 30
1789677837 64
1789677842 64
1789677847 31
1789677852 31
1789677857 31
1789677862 31
1789677867 31
1789677872 31
1789677877 31
1789677882 31
1789677887 31
1789677892 31
1789677897 31
1789677902 31
1789677907 31
```
</details>

---

