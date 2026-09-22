---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:32:53 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 74-96 cores)</summary>

```
1790093852 86
1790093857 86
1790093862 86
1790093867 86
1790093872 86
1790093877 86
1790093882 86
1790093887 86
1790093892 86
1790093897 86
1790093902 86
1790093907 86
1790093912 86
1790093917 86
1790093922 96
1790093927 96
1790093932 96
1790093937 96
1790093942 96
1790093947 96
```
</details>

---

