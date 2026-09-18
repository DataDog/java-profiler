---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:48:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1789731832 29
1789731837 29
1789731842 29
1789731847 29
1789731852 29
1789731857 29
1789731862 34
1789731867 34
1789731872 34
1789731877 34
1789731882 34
1789731887 34
1789731892 34
1789731897 34
1789731902 34
1789731907 34
1789731912 14
1789731918 14
1789731923 14
1789731928 14
```
</details>

---

