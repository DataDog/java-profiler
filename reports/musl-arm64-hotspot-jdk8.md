---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 07:59:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (8 unique values: 14-21 cores)</summary>

```
1789991750 21
1789991755 21
1789991760 21
1789991765 21
1789991770 20
1789991775 20
1789991781 17
1789991786 17
1789991791 16
1789991796 16
1789991801 16
1789991806 16
1789991811 19
1789991816 19
1789991821 18
1789991826 18
1789991831 18
1789991836 18
1789991841 19
1789991846 19
```
</details>

---

